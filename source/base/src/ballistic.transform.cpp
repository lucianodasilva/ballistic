#include "ballistic.transform.h"
#include "ballistic.game.h"
#include "ballistic.entity.h"
#include "ballistic.entity_type.h"

namespace ballistic {

	const id_t transform::component_id = id::transform;

	void transform::require_properties (entity_type * new_type, component_info & info) {																	   
		new_type->properties
			.require < vec3 > (id::transform_position)
			.require (id::transform_scale, vec3 {real (1), real (1), real (1)})
			.require < vec3 > (id::transform_rotation)
			.require < mat4 > (id::transform);
	}

	void transform::setup (ballistic::containers::property_container & parameters) {
		ballistic::component::setup (parameters);
			
		game ().global_notifier.attach (id::message::update, this);

		auto & properties = parent ().properties;

		_position = properties.aquire < vec3 > (id::transform_position);
		_rotation = properties.aquire < quat > (id::transform_rotation);
		_scale = properties.aquire < vec3 > (id::transform_scale);

		_transform = properties.aquire < mat4 > (id::transform);
		update_transform();
	}

	void transform::terminate () {
		game ().global_notifier.detach (id::message::update, this);
	}

	void transform::notify (ballistic::entity * sender, ballistic::message & message) {
		update_transform();
	}
	
	void transform::update_transform(){
		*_transform =
		//mat4::make_translation (*_position)	*
		//((quat)*_rotation).to_matrix ()	*
		//mat4::make_scale (*_scale);
		mat4::make_scale(*_scale) *
		mat4::make_translation(*_position)
		
		;
	}
}