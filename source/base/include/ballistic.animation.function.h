#ifndef _ballistic_animation_function_h_
#define _ballistic_animation_function_h_

#include "ballistic.config.h"
#include "ballistic.animation.driver.h"
#include "ballistic.entity.h"
#include "ballistic.id.h"
#include "ballistic.iresource.h"
#include "ballistic.math.vecn_t.h"
#include "ballistic.math.vectors.h"
#include "ballistic.property.h"
#include "ballistic.property_container.h"

namespace ballistic {
	namespace animation {

		class idriver;

		class ifunction {
		public:

			virtual idriver * create_driver (storyboard::action & action, entity * target, const id_t property_id) = 0;

			virtual void setup (property_container & parameters) = 0;

		};

		template < class target_value_t >
		class function : public ifunction {
		public:
			virtual void update (real t, property < target_value_t > * target) = 0;

		};

	}
}

#endif