
#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <map>

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

class component_info {
private:
	
public:
	
	inline component_info ( const string & name ) {
		
	}
	
	template < class T >
	component_info & attribute ( const string & name, T value ) {
		return *this;
	}
	
};

class entity_info {
private:
public:
	
	entity_info & component (const string & name) {
		return *this;
	}
	
	entity_info & component ( const component_info & ref ) {
		return *this;
	}
	
};

class game {
public:

	entity_info _var;
	
	inline entity_info & define (const string & name) {
		return _var;
	}
	
};


int main ( int argc, char ** argv) {

	game g;
	
	g.define ("blah")
		.component ("stuff")
		.component ("coiso")
		.component (
			component_info ("big")
					.attribute("position", vec3 (.4,.5,.7))
		)
	;
	
	return 0;

	_frontend = create_frontend (point ( 1024, 700));
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->set_clear_color(color (.0, .6, 1., 1.));
	
	_game = new ballistic::game ();
	_game->on_initialize ();

	ballistic::component::define < ballistic::graphics::system_component > ("graphics_system");
	((ballistic::graphics::system_component *)_game->create_component ("graphics_system"))->set_device (_device);
	
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
	
	_mesh->set_data(vbuffer, index);
	_frontend->do_event_loop (_game);

	return 0;
}