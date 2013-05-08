#include <stdlib.h>
#include <stdio.h>

#include <Ballistic.h>
#include <ballistic.graphics.h>

#include <glm.hpp>
#include <ext.hpp>


using namespace ballistic::engine;
using namespace ballistic::graphics;

GLFWwindow* window;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void rotate_component ( ballistic::engine::entity * this_entity, ballistic::engine::message & message ) {
	
	if (message.get_id () != message_update)
		return;
	
	float time = message [message_game_time];
	float angle = 180.0F * time;
	
	glm::vec3 pos = this_entity->attribute("position").get().as < glm::vec3 > ();
	
	if (pos.x < 0.0F) {
		angle = 360.0F - (angle / 2.0F);
	}
	
	glm::mat4 transform = glm::translate (pos);
	transform = glm::rotate(transform, angle, 0.0F, 0.0F, 1.0F);
	
	//glm::mat4 transform = glm::rotate(angle, 0.0F, 0.0F, 1.0F);
	//glm::vec3 pos = this_entity->attribute("position").get().as < glm::vec3 > ();
	//transform = glm::translate (transform, pos);
	
	this_entity->attribute (visual_component::transform_attribute_id).set (transform);
}

void setup (ballistic::engine::game *& game) {

	game = new ballistic::engine::game ();

	// Define rotation component
	component_factory::define < func_component < rotate_component > > ("rotate_component");
	// Define graphics components
	component_factory::define < visual_component > ("visual_component");
	// Define graphics system component
	component_factory::define < ballistic::graphics::system > ("visual_system");

	// --------------------------------------------

	// Define entity
	ballistic::engine::entity_factory::define ("demo_triangle")
		<< "rotate_component"
		<< "visual_component";

	// entities assemble... :D
	game->create_component ("visual_system");
	
	entity * ent1 = game->create_entity ("demo_triangle");
	entity * ent2 = game->create_entity ("demo_triangle");
	
	// resources
	mesh::vertex v_buffer [4] = {
		{vec3 (-1.0F, -1.0F, 0.0F)},
		{vec3 (1.0F, -1.0F, 0.0F)},
		{vec3 (1.0F, 1.0F, 0.0F)},
		{vec3 (-1.0F, 1.0F, 0.0F)}
	};

	uint16 i_buffer [6] = { 0, 1, 2, 0, 2, 3 };

	mesh * new_mesh = new mesh (v_buffer, 4, i_buffer, 6);
	
	material * mat1 = new material ();
	mat1->color = vec4 (1.0F, 0.0F, 0.0F, 1.0F);
	
	material * mat2 = new material ();
	mat2->color = vec4 (0.0F, 1.0F, 0.0F, 1.0F);

	ent1->attribute (visual_component::mesh_attribute_id).set (new_mesh);
	ent1->attribute (visual_component::material_attribute_id).set (mat1);
	ent1->attribute ("position").set (vec3(-4.0F, 0.0F, 0.0F));
	
	ent2->attribute (visual_component::mesh_attribute_id).set (new_mesh);
	ent2->attribute (visual_component::material_attribute_id).set (mat2);
	ent2->attribute ("position").set (vec3(4.0F, 0.0F, 0.0F));
}

void loop_callback ( ballistic::engine::game * game ) {

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

	ballistic::engine::game * game;

	setup (game);
	game->loop (loop_callback);
	
    glfwDestroyWindow(window);
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}