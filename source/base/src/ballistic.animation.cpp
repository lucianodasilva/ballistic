#include "ballistic.animation.h"

#include "ballistic.animation.component.h"
#include "ballistic.animation.function_implementation.h"
#include "ballistic.animation.function_type.h"
#include "ballistic.game.h"
#include "ballistic.resource_container.h"

namespace ballistic {
	namespace animation {
		
		void define_resources () {

			resource_container & container = game::instance.resources;

			container
				.add_to_global (new function_type < linear_function < vec2 > > (text_to_id ("vec2_linear")))
				.add_to_global (new function_type < linear_function < vec3 > > (text_to_id ("vec3_linear")))
				.add_to_global (new function_type < linear_function < vec4 > > (text_to_id ("vec4_linear")))
				.add_to_global (new function_type < linear_function < real > > (text_to_id ("real_linear")))
				.add_to_global (new function_type < linear_function < color > > (text_to_id ("color_linear")));

			;

			ballistic::component::declare < animation::component > ();
		}

	}
}