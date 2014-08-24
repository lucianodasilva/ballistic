#include "ballistic.graphics.font_rendering_system.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		//id_t font_rendering_system::id () {
		//	return ballistic::id::graphics::font_renderer;
		//}
		//
		//font_rendering_system::font_rendering_system () {}
		//
		//void font_rendering_system::notify (entity * sender, ballistic::message & message) {
		//
		//}
		//
		//void font_rendering_system::attach () {
		//
		//	if (game::instance.systems.contains_system (id::graphics::system))
		//		_graphics = dynamic_cast < graphics_system *> (game::instance.systems [id::graphics::system]);
		//	else {
		//		debug_print ("font renderer depends on the graphics system. fonts will be unavailable.");
		//	}
		//
		//
		//	// register for render event
		//	game::instance.global_notifier.attach (id::message::render, this);
		//}
		//
		//void font_rendering_system::detach () {
		//	game::instance.global_notifier.detach (id::message::render, this);
		//}
		//
		//void font_rendering_system::render_string (const string & text, real x, real y, uint8_t layer, iraster_font * font, color color) {
		//	
		//	//TODO: how to send text and color?
		//	//_graphics->push_item (font->material (), _mesh, layer, mat4::make_translation (vec3 ({x, y, real (0)})));
		//}

	}
}