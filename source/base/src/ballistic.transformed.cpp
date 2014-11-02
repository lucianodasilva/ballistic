#include "ballistic.transformed.h"
#include "ballistic.game.h"
#include "ballistic.entity.h"
#include "ballistic.entity_type.h"

namespace ballistic {

	const id_t transformed::component_id = id::transformed::id;

	void transformed::require_properties (entity_type * new_type, component_info & info) {																	   
		new_type->properties
			.require < vec3 > (id::position)
			.require (id::scale, vec3 {real (1), real (1), real (1)})
			.require < quat > (id::rotation)
			.require < mat4 > (id::transform);
	}

	void transformed::setup (ballistic::containers::property_container & parameters) {
		ballistic::component::setup (parameters);
			
		game ().global_notifier.attach (id::message::update, this);

		auto & properties = parent ().properties;

		_position = properties.aquire < vec3 > (id::position);
		_rotation = properties.aquire < quat > (id::rotation);
		_scale = properties.aquire < vec3 > (id::scale);

		_transform = properties.aquire < mat4 > (id::transform);
		update_transform();
	}

	void transformed::terminate () {
		game ().global_notifier.detach (id::message::update, this);
	}

	void transformed::notify (ballistic::entity * sender, ballistic::message & message) {
		update_transform();
	}
	
	void transformed::update_transform(){
		*_transform =
		//mat4::make_translation (*_position)	*
		//((quat)*_rotation).to_matrix ()	*
		//mat4::make_scale (*_scale);
		mat4::make_scale(*_scale) *
		mat4::make_translation(*_position)
		
		;
	}
}