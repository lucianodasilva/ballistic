#ifndef _ballistic_graphics_io_effect_package_reader_h_
#define _ballistic_graphics_io_effect_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace resources {

			class effect_package_type : public ballistic::ipackage_ {
			private:

				idevice * _device;

			public:

				effect_package_type (idevice * device);

				virtual string get_name ();

				virtual void load_element (
					tinyxml2::XMLElement * element,
					ballistic::resources::stack & stack
					);

			};

		}
	}
}

#endif // !_ballistic_graphics_resources_effect_package_type_h_
