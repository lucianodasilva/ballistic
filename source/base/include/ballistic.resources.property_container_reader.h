#ifndef _ballistic_resource_property_container_reader_h_
#define _ballistic_resource_property_container_reader_h_

#include "ballistic.convert.h"
#include "ballistic.property_map.h"
#include "ballistic.resources.stack.h"
#include "ballistic.math.h"

#include <string>
#include <tinyxml2.h>

namespace ballistic {
	namespace resources {;

		struct property_container_reader {

			static void read (
				tinyxml2::XMLElement * element,
				ballistic::resources::stack & stack,
				property_map & container
			);


		};
		
	}
}

#endif
