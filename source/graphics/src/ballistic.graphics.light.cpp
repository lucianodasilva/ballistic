#include "ballistic.graphics.light.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"


namespace ballistic {
	namespace graphics {

		const id_t light::component_id = id::light::id;

		light::light () :
			_system			(nullptr),
			_p_position		(nullptr),
			_p_color		(nullptr),
			_p_intensity	(nullptr),
			_p_fallout		(nullptr)
		{}

		void light::require_properties (entity_type * new_type, component_info & info) {
			new_type->properties.require < vec3 >	(id::position);
			new_type->properties.require < color >	(id::light::color, color {1., 1., 1.});
			new_type->properties.require < real >	(id::light::intensity, 1.0);
			new_type->properties.require < real >	(id::light::fallout);
		}

		void light::setup (ballistic::containers::property_container & parameters) {
			component::setup (parameters);

			_system = dynamic_cast <graphics_system *> (game ().systems [ballistic::id::graphics::system]);

			_p_position		= parent().properties.aquire < vec3 > (id::position);
			_p_color		= parent ().properties.aquire < color > (id::light::color);
			_p_intensity	= parent ().properties.aquire < real > (id::light::intensity);
			_p_fallout		= parent ().properties.aquire < real > (id::light::fallout);

			game ().global_notifier.attach (id::message::render, this);
		}

		void light::terminate () {
			game ().global_notifier.detach (id::message::render, this);
		}

		void light::notify (ballistic::entity * sender, ballistic::message & message) {
			light_info info;

			info.position	= *_p_position;
			info.color		= *_p_color;
			info.intensity	= *_p_intensity;
			info.fallout	= *_p_fallout;

			if (_system)
				_system->push_light (info);
			else
				_system = dynamic_cast <graphics_system *> (game ().systems [ballistic::id::graphics::system]);
		}

	}
}