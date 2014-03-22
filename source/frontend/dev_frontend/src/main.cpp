
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

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);

	g.systems.attach (graphics);

	// create entities
	g.entities.create (res_camera);
	g.entities.create (res_cube);

	// initialize
	g.initialize ();

	_frontend->do_event_loop ();

	return 0;
}