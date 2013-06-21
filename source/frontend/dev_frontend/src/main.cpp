
#include <ballistic.base.h>
#include <ballistic.graphics.h>

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
	return new ballistic::mac_desktop::frontend (size);
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


void update (ballistic::game * game) {
	_device->clear ();
	_device->begin_frame ();
	
	//_mesh->attach();
	//_mesh->render ();
	//_mesh->detach();
	
	_game->frame (_frontend);
	_device->end_frame();
}

int main ( int argc, char ** argv) {

	_frontend = create_frontend (point ( 1024, 700));
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->set_clear_color(color (.0, .6, 1., 1.));
	
	_game = new ballistic::game ();
	_game->on_initialize ();
	
	_mesh = _device->create_mesh();
	
	ballistic::graphics::vertex vbuffer [4]
	= {
		{vec3 (-1, -1, 0), vec2 (0, 0)},
		{vec3 (1, -1, 0), vec2 (1, 0)},
		{vec3 (1, 1, 0), vec2 (1, 1)},
		{vec3 (-1, 1, 0), vec2 (0, 1)}
	};
	
	uint16 index [6] = {
		0, 1, 3,
		3, 1, 2
	};
	
	//_mesh->set_data(&vbuffer [0], 4, &index[0], 3);

	while (_game->frame (_frontend, update)) {}

	return 0;
}