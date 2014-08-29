#include "ballistic.graphics.io.font_package_reader.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.font.h"

#include <ballistic.base.h>

#include "ballistic.graphics.itexture.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			font_package_reader::font_package_reader () {}

			const char * font_package_reader::type () const {
				return "font";
			}

			istream & font_package_reader::get_line(istream & stream, string & trim, char delimiter) {
				char c;

				trim.clear();

				while (stream.get(c).good()) {
					if (c == '\n' || c == '\r')
						continue;

					if (c == delimiter || stream.peek() == std::char_traits<char>::eof())
						return stream;

					trim.append(1, c);
				}

				return stream;
			}

			void font_package_reader::load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container) {

				const char * name = element->Attribute ("name");
				
				font * mat  = new font (text_to_id (name));
				
				auto * cursor = element->FirstAttribute ();
				
				while (cursor) {
					if (strcmp(cursor->Name(), "diffuse") == 0) {
						color tmp;
						color::parse(cursor, tmp);
						mat->diffuse = tmp;
					}
					else if (strcmp(cursor->Name(), "opaque") == 0) {
						mat->opaque = convert_to < bool >(cursor->Value());
					} else if (strcmp(cursor->Name(), "texture") == 0) {
						itexture * texture = container[text_to_id(cursor->Value())];
						mat->texture = texture;
					} else if (strcmp(cursor->Name(), "metrics") == 0) {
						stringstream ss(cursor->Value());
						string value;

						real * real_buffer = (+mat->font_metrics[0].data);
						uint32_t real_index = 0;
						while (get_line(ss, value, ',')) {
							if (real_index > 256 << 1) {
								debug_error("font metrics larger than expected!");
								break;
							}

							real_buffer[real_index] = convert_to < real >(value);
							++real_index;
						}

						if (real_index < 256 << 1) {
							debug_error("font metrics must represent the full ascii table!");
						}
					} else if (strcmp (cursor->Name (), "name") == 0) {
					} else {
						debug_print("unknown font property \"" << cursor->Name () << "\"");
					}
				
					cursor = cursor->Next ();
				}
				
				container.add_to_level (mat);
			}

		}
	}
}