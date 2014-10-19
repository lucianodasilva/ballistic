
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.frontend.h>

#undef far
#undef near

#include "entities.h"
#include "resources.h"

using namespace ballistic;

#ifdef BALLISTIC_OS_WINDOWS
ballistic::ifrontend * create_frontend (game & game_ref, const point & size ) {
	return new ballistic::win_desktop::frontend (game_ref, size);
}
#elif defined (BALLISTIC_OS_DARWIN)
#	include <GLUT/GLUT.h>
ballistic::ifrontend * create_frontend (const point & size) {
	return new ballistic::mac_desktop::frontend (size);
}
#endif

#ifdef BALLISTIC_DESKTOP_GL
#	include <ballistic.graphics.opengl.h>

ballistic::graphics::idevice * create_device () {
	return new ballistic::graphics::opengl_device ();
}
#endif

ballistic::ifrontend *			_frontend;
ballistic::graphics::idevice *	_device;

void initialize_defaults (game & g) {
	g.initialize ();

	_frontend = create_frontend (g, {300, 300});
	_frontend->create ();
	_frontend->show ();

	// setup graphics stuffs
	_device = create_device ();
	_device->clear_color ({.0F, .6F, 1.F, 1.F});

	g.frontend (_frontend);


	ballistic::graphics::define_resources (g, _device);

	auto graphics = new ballistic::graphics::graphics_system (g);
	graphics->device (_device);
	graphics->material_effect (g.resources [res_default_material]);
	graphics->overlay_effect (g.resources [res_overlay_material]);

	g.systems.attach (graphics);
}

bool load_instances (game & g, int argc, char ** argv) {

	graphics::imesh *		mesh = nullptr;
	graphics::material *	material = nullptr;
	graphics::rig *			rig = nullptr;

	switch (argc) {
	case (4) :
	{
		res_id_t
			mesh_id (argv [1], argv [3]),
			material_id (argv [2], argv [3]);

		mesh = g.resources [mesh_id];
		material = g.resources [material_id];
		break;
	}
	default:
		std::cout << "Error. Invalid number of arguments." << std::endl;
		std::cout << "Expected model_viewer [mesh_name] [material_name] [resource_file]" << std::endl;
		return false;
	}

	if (mesh && material) {

		entity * model = g.entities.create (model_entity_type, model_entity);
		model->properties [id::graphics::mesh] = mesh;
		model->properties [id::graphics::material] = material;

		auto bb = mesh->bounding_box ();
		real camera_radius = (math::length (bb.v_max) / real (std::tan (45.0 / 2.0))) * real (1.5);

		entity * camera = g.entities.create (camera_entity_type, camera_entity);
		camera->properties [camera_controler::starting_radius] = camera_radius;

		// lights
		entity * light = nullptr;
		
		light = g.entities.create (light_entity_type);
		light->properties [id::position] = vec3{camera_radius, camera_radius, .0};
		light->properties [id::graphics::light_color] = color {0.1, 0.5, 1., 1.};
		light->properties [id::graphics::light_fallout] = real (camera_radius * 2.0);

		light = g.entities.create (light_entity_type);
		light->properties [id::position] = vec3{camera_radius, .0, camera_radius};
		light->properties [id::graphics::light_color] = color{1.0, 1.0, 1., 1.};
		light->properties [id::graphics::light_fallout] = real (camera_radius * 2.0);

		light = g.entities.create (light_entity_type);
		light->properties [id::position] = vec3{-camera_radius, -camera_radius, .0};
		light->properties [id::graphics::light_color] = color{0.1, 0.1, 0.0, 0.25};
		light->properties [id::graphics::light_fallout] = real (camera_radius * 2.0);

	} else {
		std::cout << "Error. Resources Not Found." << std::endl;
		std::cout << "Expected model_viewer [mesh_name] [material_name] [resource_file]" << std::endl;
		return false;
	}

	return true;
}

int main ( int argc, char ** argv) {

	debug_init();

	game g;
	g.initialize ();
	initialize_defaults (g);

	define_internals (g);

	// load file
	if (!load_instances (g, argc, argv))
		return -1;

	g.initialize ();
	_frontend->do_event_loop ();

	return 0;
}