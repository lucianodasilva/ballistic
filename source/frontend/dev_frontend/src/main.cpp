
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

ballistic::res_id_t res_rotating_square ("rotating_square", "resources/game.xml");

// ------------------------------------------------------------------------------
/*
@ http://www.sjbaker.org/steve/omniv/love_your_z_buffer.html

z_buffer_value = (1 << N) * (a + b / z)

Where:

N = number of bits of Z precision
	a = zFar / (zFar - zNear)
	b = zFar * zNear / (zNear - zFar)
	z = distance from the eye to the object

	...and z_buffer_value is an integer.
  */

struct render_bucket {

	union {
		uint32 data;

		struct {
			uint8	_b0;
			uint8	_b1;
			uint8	_b2;
			uint8	_b3;
		};
	};

	inline void set_value (int8 layer, bool translucent, uint16 depth, uint8 material) {
		// set layer
		_b0 = (layer << 1);
		// set translucent
		if (translucent) {
			_b0 ^= 0x01;
			_b1 = material;
			*((uint16 *)&_b2) = depth;
		} else {
			_b0 |= 0x01;
			*((uint16 *)&_b1) = depth;
			_b3 = material;
		}

	}

	inline bool get_translucent () { return _b0 & 0x01; }

	inline int8 get_layer () { return (_b0 >> 1) & 0x7F; }


	inline uint16 get_depth () {
		return get_depth (get_translucent ());
	}

	inline uint16 get_depth (bool translucent) {
		if (translucent)
			return *(uint16 *)&_b2;
		else
			return *(uint16 *)&_b1;
	}

	inline uint8 get_material () {
		return get_material (get_translucent ());
	}

	inline uint8 get_material (bool translucent) {
		if (translucent)
			return _b3;
		else
			return _b1;
	}
};

int main ( int argc, char ** argv) {

	_frontend = create_frontend (point ( 1024, 700));
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->set_clear_color(color (.0, .6, 1., 1.));
	
	_game = new ballistic::game ();
	
	_game->on_initialize ();

	_game->define_component < ballistic::graphics::system_component > ("graphics_system");
	
	auto graphics_system
		= _game->create_component < ballistic::graphics::system_component > ("graphics_system");

	graphics_system->set_device (_device);

	_game->add_component (graphics_system);
	//ballistic::component::define < ballistic::graphics::system_component > ("graphics_system");
	//((ballistic::graphics::system_component *)_game->create_component ("graphics_system"))->set_device (_device);
	
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