#ifndef _ballistic_transform_h_
#define _ballistic_transform_h_

#include "ballistic.component.h"
#include "ballistic.math.h"
#include "ballistic.math.quat.h"
#include "ballistic.math.matrixes.h"

namespace ballistic {

	class transform : public ballistic::component {
	private:

		property < vec3 > * _position;
		property < quat > * _rotation;
		property < vec3 > * _scale;

		property < mat4 > * _transform;

	public:

		static const id_t component_id;

		transform ();

		static void require_properties (entity_type * new_type, component_info & info);

		virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters);

		virtual void terminate ();

		virtual void notify (ballistic::entity * sender, ballistic::message & message);
		
		virtual void update_transform ();

	};

}

#endif