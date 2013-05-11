#include <stdlib.h>
#include <stdio.h>

#include <Ballistic.h>
#include <ballistic.graphics.h>

#include <glm.hpp>
#include <ext.hpp>


using namespace ballistic;
using namespace ballistic::graphics;

GLFWwindow *		_window;
ballistic::game *	_game;

double				_lx, _ly;
bool				_mouse_down = false;

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static void mouse_scroll (GLFWwindow* window,double x,double y) {
	if (y != 0.0) {
		message m (_game, std::hash < std::string > ()("mouse_moved"));
		m ["mouse_move_vector"] = glm::vec3 (0, 0, y / 250.0F);
		
		_game->send_message(m);
	}
}

static void mouse_down (GLFWwindow * window, int button, int state) {
	_mouse_down = button == 0 && state;
}

static void mouse_moved ( GLFWwindow * window, double x, double y ) {
	
	if (_mouse_down) {
		message m (_game, std::hash < std::string > ()("mouse_moved"));
		m ["mouse_move_vector"] = glm::vec3 (x - _lx, y - _ly, 0.0F);
		
		_game->send_message(m);
	}
	
	_lx = x;
	_ly = y;
}

void rotate_component ( ballistic::entity & this_entity, ballistic::message & message ) {
	
	if (message.get_id () != ballistic::id::message_update)
		return;
	
	float time = message [ballistic::id::game_time];
	float angle = 180.0F * time;
	
	glm::vec3 pos = this_entity ["position"];
	
	if (pos.x < 0.0F) {
		angle = 360.0F - (angle / 2.0F);
	}
	
	glm::mat4 transform = glm::translate (pos);
	transform = glm::rotate(transform, angle, 0.0F, 0.0F, 1.0F);
	
	//glm::mat4 transform = glm::rotate(angle, 0.0F, 0.0F, 1.0F);
	//glm::vec3 pos = this_entity->attribute("position").get().as < glm::vec3 > ();
	//transform = glm::translate (transform, pos);
	
	this_entity[ballistic::id::transform] = transform;
}

void camera_update_view ( ballistic::entity & this_entity, ballistic::message & message ) {
	if (message.get_id () != graphics::id::message_render)
		return;
	
	device * visual_device = message [graphics::id::render_device];
	visual_device->view_matrix () = this_entity ["view"];
	
	glm::vec3 pos = this_entity ["position"];
	visual_device->projection_matrix() = glm::ortho(-300.0F * pos.z, 300.0F * pos.z, 300.0F * pos.z, -300.0F * pos.z, 10.0F, -10.0F);
}

void camera_move ( ballistic::entity & this_entity, ballistic::message & message ) {
	
	if (message.get_id () != std::hash < std::string > ()("mouse_moved"))
		return;
	
	glm::vec3 mov_vec = message ["mouse_move_vector"];
	glm::vec3 pos = this_entity ["position"];
	
	pos += mov_vec;
	
	this_entity ["position"] = pos;
	// view matrix, must be inverted so we invert
	// the position
	this_entity ["view"] = glm::translate(-pos.x * pos.z, -pos.y * pos.z, 0.0F);
}

void setup (ballistic::game *& game) {

	game = new ballistic::game ();

	// Define rotation component
	component_factory::define < func_component < rotate_component > > ("rotate_component");
	// Define graphics components
	component_factory::define < visual > ("visual");
	// Define graphics system component
	component_factory::define < ballistic::graphics::device > ("visual_device");
	
	// Define camera component
	component_factory::define < func_component< camera_update_view > > ("camera_update_view");
	component_factory::define < func_component< camera_move > > ("camera_move");

	// --------------------------------------------

	// Define entity
	ballistic::entity_factory::define ("demo_quad")
		<< "rotate_component"
		<< "visual";
	
	ballistic::entity_factory::define ("camera")
		<< "camera_move"
		<< "camera_update_view";

	// entities assemble... :D
	graphics::device * graph_dev = (graphics::device *)game->create_component ("visual_device");
	graph_dev->projection_matrix() = glm::ortho(-300.0F, 300.0F, 300.0F, -300.0F, 10.0F, -10.0F);
	
	entity & cam = game->create_entity ("camera");
	cam ["position"] = glm::vec3 (0.0F, 0.0F, 1.0F);
	
	entity & ent1 = game->create_entity ("demo_quad");
	entity & ent2 = game->create_entity ("demo_quad");
	
	// resources
	mesh::vertex v_buffer [4] = {
		{vec3 (-50.0F, -50.0F, 0.0F)},
		{vec3 (50.0F, -50.0F, 0.0F)},
		{vec3 (50.0F, 50.0F, 0.0F)},
		{vec3 (-50.0F, 50.0F, 0.0F)}
	};

	::uint16 i_buffer [6] = { 0, 1, 2, 0, 2, 3 };

	mesh * new_mesh = new mesh (v_buffer, 4, i_buffer, 6);
	
	material * mat1 = new material ();
	mat1->color = vec4 (1.0F, 0.0F, 0.0F, 1.0F);
	
	material * mat2 = new material ();
	mat2->color = vec4 (0.0F, 1.0F, 0.0F, 1.0F);

	ent1 [graphics::id::mesh] = new_mesh;
	ent1 [graphics::id::material] = mat1;
	ent1 ["position"] = vec3(-150.0F, 0.0F, 0.0F);
	
	ent2 [graphics::id::mesh] = new_mesh;
	ent2 [graphics::id::material] = mat2;
	ent2 ["position"] = vec3(150.0F, 0.0F, 0.0F);
}

void loop_callback ( ballistic::game * game ) {
	
	if (glfwWindowShouldClose(_window))
		game->terminate ();

	glfwSwapBuffers(_window);
	glfwPollEvents();

}

int main(void)
{
    glfwSetErrorCallback(error_callback);
	
    if (!glfwInit())
        exit(EXIT_FAILURE);
	
    _window = glfwCreateWindow(600, 600, "Simple example", NULL, NULL);
	
	glfwSetScrollCallback(_window, mouse_scroll);
	glfwSetMouseButtonCallback(_window, mouse_down);
	glfwSetCursorPosCallback(_window, mouse_moved);
	
    if (!_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	
    glfwMakeContextCurrent(_window);
	
	glewInit ();
	
	glViewport(0, 0, 600, 600);

	setup (_game);
	_game->loop (loop_callback);
	
    glfwDestroyWindow(_window);
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}