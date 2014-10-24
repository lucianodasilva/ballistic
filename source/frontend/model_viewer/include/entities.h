#ifndef	_ballistic_model_viewer_entities_h_
#define _ballistic_model_viewer_entities_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include "camera_controller.h"
#include "fps_counter.h"
#include "resources.h"
#include "ui_controller.h"

using namespace ballistic;

define_id_ext (camera_entity_type, "camera.entity_type");
define_id (camera_entity);
define_id_ext (model_entity_type, "model.entity_type");
define_id (model_entity);
define_id_ext (fps_counter_entity_type, "fps_counter.entity_type");
define_id (fps_counter_entity);

define_id_ext (ui_entity_type, "ui.entity_type");
define_id (ui_entity);

define_id_ext (light_entity_type, "light.entity_type");

inline void define_internals (game & g) {
	// load resources
	g.resources.load (default_res_file);

	// define components
	component::declare < camera_controller > (g);
	component::declare < fps_counter > (g);

	// define entity types

	// create camera
	{
		entity_type * camera_type = entity_type::declare <
			graphics::camera,
			camera_controller
		>
		(g, camera_entity_type);

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

	// create light
	{
		entity_type::declare <
			graphics::light
		> (g, light_entity_type);
	}

	// create fps counter
	{
		auto fps_counter_type = entity_type::declare <
			fps_counter,
			ballistic::transform,
			graphics::overlay_text
		> (g, fps_counter_entity_type);

		auto & fps_props = fps_counter_type->properties;

		fps_props [id::transform_position] = vec3{-.9, .9, .0};
		fps_props [id::transform_scale] = vec3{.05, .05, .05};
		fps_props [id::graphics::text::font_id] = text_to_id ("consolas_16.font");
	}

	// create model
	{
		entity_type * model_type = entity_type::declare <
			ballistic::transform,
			graphics::visual
		> (g, model_entity_type);
	}

	// create ui
	{
		entity_type::declare <
			ui_controller
		> (g, ui_entity_type);
	}

	// create entities
	g.entities.create (fps_counter_entity_type, fps_counter_entity);
	g.entities.create (ui_entity_type, ui_entity);

}

#endif