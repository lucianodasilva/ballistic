#ifndef _ballistic_graphics_io_material_package_reader_h_
#define _ballistic_graphics_io_material_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			class material_package_reader : public ballistic::io::package_loader::ipackage_element_reader {
			private:

				idevice * _device;

			public:

				material_package_reader (idevice * device);

				virtual string name ();

				virtual void load_element (
					tinyxml2::XMLElement * element,
					ballistic::resource_container & container
				);

			};

		}
	}
}

#endif //!_ballistic_graphics_resources_material_loader_h_
