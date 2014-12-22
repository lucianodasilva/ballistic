
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.graphics.opengl.h>
#include <ballistic.frontend.h>

#include <map>
#include <chrono>
#include <limits>

using namespace ballistic;

ballistic::ifrontend *			_frontend;
ballistic::graphics::imesh *	_mesh;

ballistic::res_id_t 
	//res_rig ("rigged.entity", "resources/rigging.xml"),
	//res_overlay_text ("overlay_text.entity", "resources/rigging.xml"),
	//res_camera ("camera.entity", "resources/rigging.xml"),
	res_default_material ("default_material.effect", "resources/default_material.fx"),
	res_overlay_material ("overlay_material.effect", "resources/overlay_material.fx");

define_id_ext(camera_entity_type, camera.entity_type);
define_id_ext(camera_entity, camera.entity);

int main ( int argc, char ** argv) {

	debug_init();

	game g;

	// create frontend
	_frontend = ballistic::create_frontend();
	_frontend->initialize(&g, {300, 300});
	
	// setup graphics stuffs
	graphics::idevice * g_dev = new graphics::opengl_device ();
	
	g_dev->clear_color ({.0F, .6F, 1.F});

	ballistic::graphics::define_resources (g, g_dev);

	auto graphics = new ballistic::graphics::graphics_system (g);
	graphics->device (g_dev);
	graphics->material_effect (g.resources [res_default_material]);
	graphics->overlay_effect (g.resources [res_overlay_material]);

	g.systems.attach (graphics);

	// initialize
	g.initialize ();
	
	// create entities
	{
		/*
		<entity_type name="camera.entity"
		position="0,0,2"
		target="0,0,0"
		up="0,1,0"
		>
		<graphics.camera projection="perspective" fov="45" near="0.1" far="100"/>
		<animation storyboard_id="camera.animation"/>
		</entity_type>
		*/
		entity_type::declare <
			ballistic::graphics::camera,
			ballistic::transformed
		>
		(g, camera_entity_type);
		
		g.entities.create (camera_entity_type, camera_entity);
	}

	_frontend->do_event_loop ();

	return 0;
}