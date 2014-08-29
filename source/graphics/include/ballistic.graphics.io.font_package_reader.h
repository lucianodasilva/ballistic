#ifndef _ballistic_graphics_io_font_package_reader_h_
#define _ballistic_graphics_io_font_package_reader_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		namespace io {

			class font_package_reader : public ballistic::io::ipackage_group_reader {
			private:
				istream & get_line(istream & stream, string & trim, char delimiter);
			public:

				font_package_reader ();

				virtual const char * type () const;

				virtual void load_element (
					const tinyxml2::XMLElement * element,
					ballistic::resource_container & container
				);

			};

		}
	}
}

#endif //!_ballistic_graphics_resources_font_loader_h_
