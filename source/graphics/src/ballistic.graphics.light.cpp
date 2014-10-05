#include "ballistic.graphics.light.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"


namespace ballistic {
	namespace graphics {

		const id_t light::component_id = id::graphics::light;

		light::light () :
			_system (nullptr),
			_p_position (nullptr),
			_p_color (nullptr),
			_p_fallout (nullptr)
		{}

		void light::require_properties (entity_type * new_type, component_info & info) {
			new_type->properties.require < vec3 > (id::position);
			new_type->properties.require < color > (id::graphics::light_color, color {1., 1., 1., 1.});
			new_type->properties.require < real > (id::graphics::light_fallout);
		}

		void light::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
			component::setup (parent, parameters);

			_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

			_p_position = parent->properties.aquire < vec3 > (id::position);
			_p_color = parent->properties.aquire < color > (id::graphics::light_color);
			_p_fallout = parent->properties.aquire < real > (id::graphics::light_fallout);

			game::instance.global_notifier.attach (id::message::render, this);
		}

		void light::terminate () {
			game::instance.global_notifier.detach (id::message::render, this);
		}

		void light::notify (ballistic::entity * sender, ballistic::message & message) {
			light_info info;

			info.position = *_p_position;
			info.color = *_p_color;
			info.fallout = *_p_fallout;

			if (_system)
				_system->push_light (info);
			else
				_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);
		}

	}
}