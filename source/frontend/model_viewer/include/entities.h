#ifndef	_ballistic_model_viewer_entities_h_
#define _ballistic_model_viewer_entities_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include "camera_controler.h"
#include "resources.h"

using namespace ballistic;

define_id_ext (camera_entity_type, "camera.entity_type");
define_id (camera_entity);

inline void define_internals () {
	// define components
	component::declare < camera_controler > ();

	// define entity types
	game & g = game::instance;

	// create camera
	{
		entity_type * camera_type = entity_type::declare <
			graphics::camera,
			camera_controler
		>
		(camera_entity_type);

		auto & cam_props = camera_type->components [0].properties;

		cam_props [id::graphics::projection] = string ("perspective");
		cam_props [id::graphics::fov] = real (45);
		cam_props [id::graphics::near] = real (.1);
		cam_props [id::graphics::far] = real (100.0);

		auto & entity_props = camera_type->properties;
		entity_props [id::position] = vec3{.0, .0, 50.};
		entity_props [id::target] = vec3 {.0, .0, .0};
		entity_props [id::up] = vec3 {.0, 1., .0};
	}

	//create entities
	g.entities.create (camera_entity_type, camera_entity);
	g.entities.create (res_cube_entity_type);
}

#endif