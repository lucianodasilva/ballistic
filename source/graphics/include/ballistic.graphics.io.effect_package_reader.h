#ifndef _ballistic_graphics_io_effect_package_reader_h_
#define _ballistic_graphics_io_effect_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			class effect_package_reader : public ballistic::io::ipackage_element_reader {
			private:

				idevice * _device;

			public:

				effect_package_reader (idevice * device);

				virtual const char * name () const;

				virtual void load_element (
					tinyxml2::XMLElement * element,
					resource_container & container
				);

			};

		}
	}
}

#endif // !_ballistic_graphics_resources_effect_package_type_h_
