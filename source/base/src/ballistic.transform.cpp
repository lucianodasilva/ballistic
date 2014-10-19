#include "ballistic.transform.h"

namespace ballistic {

	const id_t transform::component_id = id::transform;

	transform::transform () {}


	void transform::require_properties (entity_type * new_type, component_info & info) {																	   
		new_type->properties.require_notify (id::transform_position, vec3 ());
		new_type->properties.require_notify (id::transform_scale, vec3 ({real (1), real (1), real (1)}));
		new_type->properties.require_notify (id::transform_rotation, quat());

		new_type->properties.require (id::transform, mat4 ());
	}

	void transform::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
		ballistic::component::setup (parent, parameters);
			
		parent->game ().global_notifier.attach (id::message::update, this);

		_position = parent->properties.aquire < vec3 > (id::transform_position);
		_rotation = parent->properties.aquire < quat > (id::transform_rotation);
		_scale = parent->properties.aquire < vec3 > (id::transform_scale);

		_transform = parent->properties.aquire < mat4 > (id::transform);
		update_transform();
	}

	void transform::terminate () {
		this->parent()->game ().global_notifier.detach (id::message::update, this);
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