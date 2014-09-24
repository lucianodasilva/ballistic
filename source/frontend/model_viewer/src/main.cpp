
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.frontend.h>

#undef far
#undef near

#include "entities.h"
#include "resources.h"

using namespace ballistic;

#ifdef BALLISTIC_OS_WINDOWS
ballistic::ifrontend * create_frontend ( const point & size ) {
	return new ballistic::win_desktop::frontend (size);
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

void initialize_defaults () {

	game & g = game::instance;
	g.initialize ();

	_frontend = create_frontend ({300, 300});
	_frontend->create ();
	_frontend->show ();

	// setup graphics stuffs
	_device = create_device ();
	_device->clear_color ({.0F, .6F, 1.F, 1.F});

	g.frontend (_frontend);


	ballistic::graphics::define_resources (_device);

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);
	graphics->material_effect (g.resources [res_default_material]);
	graphics->overlay_effect (g.resources [res_overlay_material]);

	g.systems.attach (graphics);
}

int main ( int argc, char ** argv) {

	debug_init();

	initialize_defaults ();

	define_internals ();

	game::instance.initialize ();
	_frontend->do_event_loop ();

	return 0;
}