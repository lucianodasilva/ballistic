#include <stdlib.h>
#include <stdio.h>

#include <Ballistic.h>
#include <ballistic.graphics.h>

GLFWwindow* window;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void rotate_component ( ballistic::engine::entity * this_entity, ballistic::engine::message & message ) {

}

using namespace ballistic::engine;
using namespace ballistic::graphics;

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
	entity * ent = game->create_entity ("demo_triangle");

	// resources
	mesh::vertex v_buffer [4] = {
		{vec3 (-1.0F, -1.0F, 0.0F), vec2 (0.0F, 0.0F)},
		{vec3 (1.0F, -1.0F, 0.0F), vec2 (0.0F, 0.0F)},
		{vec3 (1.0F, 1.0F, 0.0F), vec2 (0.0F, 0.0F)},
		{vec3 (-1.0F, 1.0F, 0.0F), vec2 (0.0F, 0.0F)}
	};

	uint16 i_buffer [6] = { 0, 1, 2, 0, 2, 3 };

	mesh * new_mesh = new mesh (v_buffer, 4, i_buffer, 6);
	material * mat = new material ();
	mat->color = vec4 (1.0F, 0.0F, 0.0F, 1.0F);

	ent->attribute (visual_component::mesh_attribute_id).set (new_mesh);
	ent->attribute (visual_component::material_attribute_id).set (mat);
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

	ballistic::engine::game * game;

	setup (game);
	game->loop (loop_callback);
	
    glfwDestroyWindow(window);
	
    glfwTerminate();
    exit(EXIT_SUCCESS);
}