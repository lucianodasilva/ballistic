#include "ballistic.graphics.resources.effect_package_type.h"

#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {
		namespace resources {

			effect_package_type::effect_package_type (idevice * device) : _device (device) {}

			string effect_package_type::get_name () {
				return "effect";
			}

			void effect_package_type::load_element (tinyxml2::XMLElement * element, ballistic::resources::stack & stack) {

				string
					name = element->Attribute ("name"),
					vs_source,
					fs_source;

				ieffect * effect = _device->create_effect ();

				tinyxml2::XMLElement * cursor = element->FirstChildElement ();

				while (cursor) {

					if (strcmp (cursor->Name (), "vertex") == 0)
						vs_source = cursor->GetText ();

					else if (strcmp (cursor->Name (), "fragment") == 0)
						fs_source = cursor->GetText ();

					cursor = cursor->NextSiblingElement ();
				}

				effect->load (vs_source, fs_source);
				stack.add_to_level (text_to_id (name.c_str ()), effect);
			}

		}
	}
}