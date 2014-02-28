#include "ballistic.graphics.io.material_package_reader.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			material_package_reader::material_package_reader (idevice * device) : _device (device) {}

			string material_package_reader::name () {
				return "material";
			}

			void material_package_reader::load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container) {

				string name = element->Attribute ("name");

				imaterial * material = _device->create_material ();
		
				const tinyxml2::XMLAttribute * cursor = element->FirstAttribute ();

				while (cursor) {

					const char * value = cursor->Value ();
					
					if (strcmp (cursor->Name (), "diffuse") == 0) {
						color tmp;
						convert_vectors(value, tmp);
						material->diffuse (tmp);
					} else if (strcmp (cursor->Name (), "specular") == 0) {
						color tmp;
						convert_vectors(value, tmp);
						material->specular (tmp);
					} else if (strcmp (cursor->Name (), "opaque") == 0) {
						material->opaque (convert_to < bool > (value));
					} else if (strcmp (cursor->Name (), "effect") == 0) {
						ieffect * effect = dynamic_cast < ieffect *> (container [text_to_id (value)]);
						
						material->effect (effect);
					}

					cursor = cursor->Next ();
				}

				container.add_to_level (text_to_id (name.c_str ()), material);
			}

		}
	}
}