#ifndef _ballistic_graphics_io_mesh_package_reader_h_
#define _ballistic_graphics_io_mesh_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			class mesh_package_reader : public ballistic::io::ipackage_group_reader {
			private:

				idevice * _device;

				static std::istream & get_line (istream & stream, string & trim, char delimiter);

			public:

				mesh_package_reader (idevice * device);

				virtual const char * type () const;

				virtual void load_element (
					const tinyxml2::XMLElement * element,
					ballistic::resource_container & container
					);

			};

		}
	}
}

#endif //!_ballistic_graphics_resource_mesh_package_reader_h_
