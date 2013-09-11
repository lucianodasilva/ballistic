#ifndef _ballistic_graphics_resources_material_package_type_h_
#define _ballistic_graphics_resources_material_package_type_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace resources {

			class material_package_type : public ballistic::resources::package_loader::itype {
			private:

				idevice * _device;

			public:

				material_package_type (idevice * device);

				virtual string get_name ();

				virtual void load_element (
					tinyxml2::XMLElement * element,
					ballistic::resources::stack & stack
				);

			};

		}
	}
}

#endif //!_ballistic_graphics_resources_material_loader_h_
