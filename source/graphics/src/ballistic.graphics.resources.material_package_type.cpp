#include "ballistic.graphics.resources.material_package_type.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {
		namespace resources {

			material_package_type::material_package_type (idevice * device) : _device (device) {}

			string material_package_type::get_name () {
				return "material";
			}

			void material_package_type::load_element (tinyxml2::XMLElement * element, ballistic::resources::stack & stack) {

				string name = element->Attribute ("name");

				imaterial * material = _device->create_material ();
		
				const tinyxml2::XMLAttribute * cursor = element->FirstAttribute ();

				while (cursor) {

					//value = string (cursor->Value ());
					//
					//if (strcmp (cursor->Name (), "diffuse") == 0) {
					//	material->set_diffuse (value);
					//} else if (strcmp (cursor->Name (), "specular") == 0) {
					//	material->set_specular (value);
					//} else if (strcmp (cursor->Name (), "opaque") == 0) {
					//	material->set_opaque (value);
					//} else if (strcmp (cursor->Name (), "effect") == 0) {
					//	ieffect * effect = dynamic_cast < ieffect *> (
					//		stack.get_resource (
					//			text_to_id ((text)value)
					//		)
					//	);
					//	
					//	
					//	material->set_effect (effect);
					//}

					cursor = cursor->Next ();
				}

				stack.add_to_level (text_to_id (name.c_str ()), material);
			}

		}
	}
}