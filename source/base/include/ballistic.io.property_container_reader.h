#ifndef _ballistic_io_property_container_reader_h_
#define _ballistic_io_property_container_reader_h_

#include "ballistic.property_container.h"
#include "ballistic.resource_container.h"

#include <tinyxml2.h>

namespace ballistic {
	namespace io {

		struct property_container_reader {

			static void read (
				tinyxml2::XMLElement * element,
				ballistic::resource_container & resources,
				property_container & container
			);


		};
	}
}

#endif
