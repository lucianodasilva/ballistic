
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.graphics.render_list.h>

#include <map>
#include <chrono>
#include <limits>

using namespace ballistic;

ballistic::ifrontend *			_frontend;
ballistic::graphics::idevice *	_device;

ballistic::graphics::imesh *	_mesh;

#ifdef BALLISTIC_OS_WINDOWS
#	include "ballistic.win_frontend.h"

ballistic::ifrontend * create_frontend ( const point & size ) {
	return new ballistic::win_desktop::frontend (size);
}

#elif defined (BALLISTIC_OS_DARWIN)
#	include "ballistic.mac_frontend.h"
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

ballistic::res_id_t res_cube ("cube.entity", "resources/test_anim.xml");
ballistic::res_id_t res_camera ("camera.entity", "resources/test_anim.xml");

// -----------
class box_brain : public ballistic::component {
private:

	real _start_time;

	property < vec3 > * _bounce;
	property < vec3 > * _start_pos;
	property < real > * _life_time;

public:

	box_brain () : _start_time (-1) {}

	static void require_properties (entity_type * new_type, component_info & info) {
		new_type->properties.require_silent < vec3 > (text_to_id ("bounce"), vec3 ());
		new_type->properties.require_silent < vec3 > (text_to_id ("start_pos"), vec3 ());
		new_type->properties.require_silent < real > (text_to_id ("life_time"), 1.0);
	}

	virtual void setup (ballistic::entity * parent, ballistic::property_container & parameters) {
		component::setup (parent, parameters);
		game::instance.global_notifier.attach (id::message_update, this);

		_bounce = parent->properties.aquire < vec3 > (text_to_id ("bounce"));
		_start_pos = parent->properties.aquire < vec3 > (text_to_id ("start_pos"));
		_life_time = parent->properties.aquire < real > (text_to_id ("life_time"));
	}

	virtual void terminate () {
		game::instance.global_notifier.detach (id::message_update, this);
	}

	virtual void notify (ballistic::entity * sender, ballistic::message & message) {

		real game_time = message [id::game_time];

		if (_start_time < real (0))
			_start_time = game_time;

		if (game_time - _start_time > *_life_time) {
			int c = std::rand () % 5 + 1;

			for (int i = 0; i < c; ++i) {
				entity * new_entity = game::instance.entities.create (res_cube);
				new_entity->properties [text_to_id ("start_pos")] = vec3 ({
					real ((std::rand () % 100) - 50),
					real (0),
					real ((std::rand () % 100) - 50)
				});
				new_entity->properties [text_to_id ("life_time")] = (real (std::rand () % 100) / real (25) + real (3));
			}

			container ()->kill ();
			return;
		}

		// update position with animation
		container ()->properties [id::position] = vec3(*_start_pos) + vec3(*_bounce);
																	 
	}

};
// -----------



int main ( int argc, char ** argv) {

	debug_init();

	_frontend = create_frontend (point{600, 600});
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->clear_color (color{.0F, .6F, 1.F, 1.F});
	
	game & g = game::instance;

	g.initialize ();

	g.frontend (_frontend);

	// setup game stuffs
	ballistic::graphics::define_resources (_device);

	component::declare < box_brain > (text_to_id ("box_brain"));

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);

	g.systems.attach (graphics);

	// create entities
	g.entities.create (res_camera);
	game::instance.entities.create (res_cube);

	// initialize
	g.initialize ();

	_frontend->do_event_loop ();

	return 0;
}