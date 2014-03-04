#include "ballistic.graphics.io.effect_package_reader.h"

#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			effect_package_reader::effect_package_reader (idevice * device) : _device (device) {}

			const char * effect_package_reader::type () const {
				return "effect";
			}

			void effect_package_reader::load_group (const string & group_name, cpptoml::toml_group & group, resource_container & container) {

				
				//const char * name = element->Attribute ("name");
				//
				//string
				//	vs_source,
				//	fs_source;
				//
				//ieffect * effect = _device->create_effect (text_to_id (name));
				//
				//tinyxml2::XMLElement * cursor = element->FirstChildElement ();
				//
				//while (cursor) {
				//
				//	if (strcmp (cursor->Name (), "vertex") == 0)
				//		vs_source = cursor->GetText ();
				//
				//	else if (strcmp (cursor->Name (), "fragment") == 0)
				//		fs_source = cursor->GetText ();
				//
				//	cursor = cursor->NextSiblingElement ();
				//}
				//
				//effect->load (vs_source, fs_source);
				//container.add_to_level (effect);
			}

		}
	}
}