#ifndef _ballistic_graphics_io_material_package_reader_h_
#define _ballistic_graphics_io_material_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			class material_package_reader : public ballistic::io::ipackage_group_reader {
			private:

				idevice * _device;

			public:

				material_package_reader (idevice * device);

				virtual const char * type () const;

				virtual void load_group (
					const string & group_name,
					cpptoml::toml_group & group,
					ballistic::resource_container & container
				);

			};

		}
	}
}

#endif //!_ballistic_graphics_resources_material_loader_h_
