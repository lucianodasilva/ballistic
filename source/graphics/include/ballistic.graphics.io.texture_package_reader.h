#ifndef _ballistic_graphics_io_texture_package_reader_h_
#define _ballistic_graphics_io_texture_package_reader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.itexture.h"

namespace ballistic {
	namespace graphics {		   
		namespace io {

			class texture_package_reader : public ballistic::io::ipackage_group_reader {
			private:

				idevice * _device;

				texture_wrap text_to_wrap (const char * value);
				texture_filter text_to_filter (const char * value);

				bool load_file (const char * filename, char *& data, texture_format & format, uint32_t & width, uint32_t & height);

			public:

				texture_package_reader (idevice * device);

				virtual const char * type () const;

				virtual void load_element (
					const tinyxml2::XMLElement * element,
					resource_container & container
				);

			};

		}
	}
}

#endif // !_ballistic_graphics_resources_texture_package_type_h_
