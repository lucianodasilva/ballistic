#include <stdlib.h>
#include <stdio.h>

#include <Ballistic.h>
#include <ballistic.graphics.h>

#include <glm.hpp>
#include <ext.hpp>


using namespace ballistic;
using namespace ballistic::graphics;

GLFWwindow* window;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void rotate_component ( ballistic::entity & this_entity, ballistic::message & message ) {
	
	if (message.get_id () != ballistic::id::message_update)
		return;
	
	float time = message [ballistic::id::game_time];
	float angle = 180.0F * time;
	
	glm::vec3 pos = this_entity ["position"].as < glm::vec3 > ();
	
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

void setup (ballistic::game *& game) {

	game = new ballistic::game ();

	// Define rotation component
	component_factory::define < func_component < rotate_component > > ("rotate_component");
	// Define graphics components
	component_factory::define < visual > ("visual");
	// Define graphics system component
	component_factory::define < ballistic::graphics::device > ("visual_device");

	// --------------------------------------------

	// Define entity
	ballistic::entity_factory::define ("demo_quad")
		<< "rotate_component"
		<< "visual";

	// entities assemble... :D
	game->create_component ("visual_device");
	
	entity & ent1 = game->create_entity ("demo_quad");
	entity & ent2 = game->create_entity ("demo_quad");
	
	// resources
	mesh::vertex v_buffer [4] = {
		{vec3 (-1.0F, -1.0F, 0.0F)},
		{vec3 (1.0F, -1.0F, 0.0F)},
		{vec3 (1.0F, 1.0F, 0.0F)},
		{vec3 (-1.0F, 1.0F, 0.0F)}
	};

	::uint16 i_buffer [6] = { 0, 1, 2, 0, 2, 3 };

	mesh * new_mesh = new mesh (v_buffer, 4, i_buffer, 6);
	
	material * mat1 = new material ();
	mat1->color = vec4 (1.0F, 0.0F, 0.0F, 1.0F);
	
	material * mat2 = new material ();
	mat2->color = vec4 (0.0F, 1.0F, 0.0F, 1.0F);

	ent1 [graphics::id::mesh] = new_mesh;
	ent1 [graphics::id::material] = mat1;
	ent1 ["position"] = vec3(-4.0F, 0.0F, 0.0F);
	
	ent2 [graphics::id::mesh] = new_mesh;
	ent2 [graphics::id::material] = mat2;
	ent2 ["position"] = vec3(4.0F, 0.0F, 0.0F);
}

void loop_callback ( ballistic::game * game ) {

	
	
	if (glfwWindowShouldClose(window))
		game->terminate ();

	glfwSwapBuffers(window);
	glfwPollEvents();

}

int main(void)
{
    glfwSetErrorCallback(error_callback);
	
    if (!glfwInit())
        exit(EXIT_FAILURE);
	
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	
    glfwMakeContextCurrent(window);
	
	glewInit ();
	
	glViewport(0, 0, 640, 480);
	glOrtho(-10, 10, 10, -10, 10, -10);

	ballistic::game * game;

	setup (game);
	game->loop (loop_callback);
	
    glfwDestroyWindow(window);
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}