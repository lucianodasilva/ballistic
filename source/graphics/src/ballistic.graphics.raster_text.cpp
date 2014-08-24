#include "ballistic.graphics.raster_text.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.material.h"

#include "ballistic.graphics.iraster_font.h"

namespace ballistic {
	namespace graphics {

		//const id_t raster_text::component_id = ballistic::id::graphics::raster_text;

		//void raster_text::require_properties (entity_type * new_type, component_info & info) {
		//	
		//	new_type->properties.require_silent < mat4 > (id::transform, mat4 ());
		//	new_type->properties.require_silent < uint8_t > (id::graphics::layer, 0);

		//	new_type->properties.require_silent < string > (id::graphics::text::text, "");
		//	new_type->properties.require_silent < id_t > (id::graphics::text::font_id, id::null);

		//	new_type->properties.require_silent < iraster_font * > (id::graphics::material, nullptr);

		//}

		//void raster_text::setup (entity * parent, property_container & parameters)
		//{
		//	component::setup (parent, parameters);

		//	game::instance.global_notifier.attach (id::message::render, this);

		//	_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

		//	_font = parent->properties.aquire < iraster_font * > (
		//		id::graphics::text::font
		//	);

		//	_transform = parent->properties.aquire < mat4 > (id::transform);
		//	_layer = parent->properties.aquire < uint8_t > (id::graphics::layer);

		//	if (!*_font)
		//		*_font = game::instance.resources [
		//			parent->properties [id::graphics::text::font_id].as < id_t >()
		//		].as < iraster_font > () ;

		//	_mesh = game::instance.resources [id::graphics::mesh_quad_one];
		//}

		//void raster_text::terminate () {
		//	game::instance.global_notifier.detach (id::message::render, this);
		//}

		//raster_text::raster_text ()
		//	:
		//	_transform (nullptr),
		//	_layer (nullptr),
		//	_font (nullptr),
		//	_text (nullptr),
		//	_system (nullptr)
		//{}

		//void raster_text::notify ( entity * sender, ballistic::message & message ) {

		//	iraster_font * font = *_font;
		//	
		//	if (!font) {
		//		debug_print ("missing font instance. text will not render");
		//		return;
		//	}

		//	// set text
		//	font->text (*_text);
		//	
		//	if (
		//		_system &&
		//		font &&
		//		font->effect () &&
		//		_mesh
		//	){
		//		_system->push_item (font, _mesh, *_layer, *_transform);
		//	} else {
		//		debug_print ("incomplete raster_text component. will not render!");
		//	}

		//}

	}
}