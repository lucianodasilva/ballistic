
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

// --------------------------------------------------
#include <tinyxml2.h>

class ireadable {
public:
	
	virtual ~ireadable () {}
	
};

class entity : public ireadable {
public:
	
	
	
};

struct faux_factory {
	
	static string handles () {
		return "entity";
	}
	
	static ireadable * read (tinyxml2::XMLElement * source) {
		return new entity ();
	}
	
};

class i_readable_factory {
public:
	virtual ireadable * read (tinyxml2::XMLElement * source) = 0;
};

template < class T >
class readable_factory : public i_readable_factory {
public:
	
	virtual ireadable * read (tinyxml2::XMLElement * source) {
		return T::read (source);
	}
	
};

class reader {
public:
	
	typedef std::map < string, i_readable_factory * > factory_map_t;
	
private:
	
	static factory_map_t _factory_map;
	
public:
	
	template < class T >
	static void define () {
		_factory_map [T::handles ()] = new readable_factory<T> ();
	}

	static ireadable * read (tinyxml2::XMLElement * source ) {
		factory_map_t::iterator it = _factory_map.find (source->Name());
		
		if (it == _factory_map.end ())
			throw "Undefind element type found!";
		
		i_readable_factory * fact = it->second;
		
		return fact->read(source);
	}
	
};

reader::factory_map_t reader::_factory_map;

// --------------------------------------------------

int main ( int argc, char ** argv) {
	
	entity * ent;
	
	tinyxml2::XMLDocument doc;
	doc.Parse(
			  "<entity name=\"yada\">"
			  "		<vec3 name=\"yada\"/>"
			  "</entity>"
			  "<entity>"
			  "</entity>"
	);
	
	reader::define < faux_factory > ();
	ent = dynamic_cast < entity * > (reader::read (doc.RootElement ()));
	
	
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