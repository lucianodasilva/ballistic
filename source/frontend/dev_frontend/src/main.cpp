
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

#ifdef BALLISTIC_OS_WINDOWS
#	include "ballistic.win_frontend.h"

ballistic::ifrontend * create_frontend ( const point & size ) {
	return new ballistic::win_desktop::frontend (size);
}

#elif defined (BALLISTIC_OS_MACOSX)
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

void circle_camera ( ballistic::entity * parent, ballistic::message & message ) {

	if (message.get_id () != ballistic::id::message_update)
		return;

	vec3 pos;

	pos.x = cos (angle) * radius;
	pos.y = 2.F;
	pos.z = sin (angle) * radius;

	angle = message [ballistic::id::game_time].as < real > () * real (1); // one radian per second
	//radius += 0.025;
	
	//if (angle > (3.1415926 * 2.)) {
	//	angle = 0.0;
	//	//radius = 1.0;
	//}

	parent->get_property (ballistic::id::position) = pos;
}

ballistic::res_id_t res_rotating_square ("rotating_square.entity", "resources/game.xml");
ballistic::res_id_t res_camera ("camera.entity", "resources/game.xml");

int main ( int argc, char ** argv) {
	
	debug_init();

	_frontend = create_frontend (point ( 800, 800));
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->set_clear_color(color (.0F, .6F, 1.F, 1.F));
	
	_game = new ballistic::game ();
	_game->set_frontend (_frontend);

	// setup game stuffs
	ballistic::graphics::define_resources (_game, _device);
	ballistic::component::define < ballistic::_func_component < &circle_camera > > (_game, ballistic::string_to_id ("orbit_cam"));

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->set_device (_device);

	_game->add_system (graphics);

	// create entities
	ballistic::entity * camera = ballistic::entity::create (_game, res_camera);
	ballistic::entity * rot_square = ballistic::entity::create (_game, res_rotating_square);

	// initialize
	_game->initialize ();

	_frontend->do_event_loop (_game);

	return 0;
}