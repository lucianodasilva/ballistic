
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.graphics.render_list.h>

#include <map>
#include <chrono>
#include <limits>

ballistic::game *				_game;
ballistic::ifrontend *			_frontend;
ballistic::graphics::idevice *	_device;

ballistic::graphics::imesh *	_mesh;

#ifdef BALLISTIC_WIN
#	include "ballistic.win_frontend.h"

ballistic::ifrontend * create_frontend ( const point & size ) {
	return new ballistic::win_desktop::frontend (size);
}

#elif defined (BALLISTIC_MACOSX)
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

#ifdef BALLISTIC_DESKTOP_DX
#	include <ballistic.graphics.directx.h>

ballistic::graphics::idevice * create_device () {
	return new ballistic::graphics::dx_device (
		((ballistic::win_desktop::frontend *)_frontend)->get_window_handle ()
	);
}

#endif

ballistic::res_id_t res_rotating_square ("rotating_square", "resources/game.xml");

int main ( int argc, char ** argv) {
	
	debug_init();

	_frontend = create_frontend (point ( 300, 300));
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->set_clear_color(color (.0F, .6F, 1.F, 1.F));
	
	_game = new ballistic::game ();

	// setup game stuffs
	ballistic::graphics::define_resources (_game, _device);
	
	_game->get_property (ballistic::graphics::id::graphics_device) = _device;

	_game->add_component (
		_game->create_component (ballistic::graphics::id::system_component));

	// create entities
	ballistic::entity * rot_square = _game->create_entity (res_rotating_square);

	// initialize
	_game->on_initialize ();

	_frontend->do_event_loop (_game);

	return 0;
}