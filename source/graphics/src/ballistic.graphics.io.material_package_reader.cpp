#include "ballistic.graphics.io.material_package_reader.h"

#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.itexture.h"
#include "ballistic.graphics.material.h"

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		namespace io {

			material_package_reader::material_package_reader () {}

			const char * material_package_reader::type () const {
				return "material";
			}

			void material_package_reader::load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container) {

				const char * name = element->Attribute ("name");
				
				material * mat  = new material (text_to_id (name));
				
				auto * cursor = element->FirstAttribute ();
				
				while (cursor) {

					if (strcmp (cursor->Name (), "diffuse") == 0) {
						color tmp;
						color::parse (cursor, tmp);
						mat->diffuse = tmp;
					} else if (strcmp (cursor->Name (), "opaque") == 0) {
						mat->opaque = convert_to < bool > (cursor->Value());
					} else if (strcmp (cursor->Name (), "texture") == 0) {
						itexture * texture = container [text_to_id (cursor->Value ())];
						mat->texture = texture;
					} else if (strcmp (cursor->Name (), "name") == 0) {
					} else {
						debug_print("unknown material property \"" << cursor->Name () << "\"");
					}
				
					cursor = cursor->Next ();
				}
				
				container.add_to_level (mat);
			}

		}
	}
}