
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

float angle = 0.0F;
float radius = 4.0F;

class orbit_camera : public ballistic::component {
public:

	virtual void setup (ballistic::entity * parent) {
		component::setup (parent);
		parent->local_notifier.attach (ballistic::id::message_update, this);
	}

	virtual void terminate () {
		container ()->local_notifier.detach (ballistic::id::message_update, this);
	}

	virtual void notify (ballistic::entity * parent, ballistic::message & message) {

		vec3 pos;

		pos.x = cos (angle) * radius;
		pos.y = 2.F;
		pos.z = sin (angle) * radius;

		angle = (real)message [ballistic::id::game_time] * real (1); // one radian per second

		parent->properties [ballistic::id::position] = pos;
	}

};

ballistic::res_id_t res_rotating_square ("rotating_square.entity", "resources/game.xml");
ballistic::res_id_t res_camera ("camera.entity", "resources/game.xml");

int main ( int argc, char ** argv) {

	debug_init();

	_frontend = create_frontend (point{150, 150});
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->clear_color (color{.0F, .6F, 1.F, 1.F});
	
	game & g = game::instance;

	g.frontend (_frontend);

	// setup game stuffs
	ballistic::graphics::define_resources (_device);

	g.resources.add_to_global (new component_constructor < orbit_camera > (text_to_id ("orbit_camera")));

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);

	g.systems.attach (graphics);

	// create entities
	g.entities.create (
		g.resources.get_resource < entity_type > (res_camera)
	);
	g.entities.create (
		g.resources.get_resource < entity_type > (res_rotating_square)
	);

	// initialize
	g.initialize ();

	_frontend->do_event_loop ();

	return 0;
}