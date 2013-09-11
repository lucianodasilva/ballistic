#include "ballistic.graphics.resources.material_package_type.h"

#include "ballistic.graphics.imaterial.h"

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

				var value;

				const tinyxml2::XMLAttribute * cursor = element->FirstAttribute ();
				while (cursor) {

					if (strcmp (cursor->Name (), "diffuse") == 0) {
						ballistic::resources::property_container_reader::default_type_reader (
							"color",
							cursor->Value (),
							stack,
							value
						);

						material->set_diffuse (value.as <color>());
					} else if (strcmp (cursor->Name (), "specular") == 0) {
						ballistic::resources::property_container_reader::default_type_reader (
							"color",
							cursor->Value (),
							stack,
							value
							);

						material->set_specular (value.as <color>());
					} else if (strcmp (cursor->Name (), "opaque") == 0) {
						ballistic::resources::property_container_reader::default_type_reader (
							"bool",
							cursor->Value (),
							stack,
							value
							);

						material->set_opaque (value.as <bool>());
					}

					cursor = cursor->Next ();
				}

				stack.add_to_level (string_to_id (name), material);
			}

		}
	}
}