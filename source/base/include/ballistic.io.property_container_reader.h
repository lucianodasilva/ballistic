#ifndef _ballistic_io_property_container_reader_h_
#define _ballistic_io_property_container_reader_h_

#include "ballistic.property_container.h"
#include "ballistic.resource_container.h"

#include <cpptoml.h>

namespace ballistic {
	namespace io {

		struct property_container_reader {

			static void read (
				cpptoml::toml_group & group,
				ballistic::resource_container & resources,
				property_container & container
			);


		};
	}
}

#endif
