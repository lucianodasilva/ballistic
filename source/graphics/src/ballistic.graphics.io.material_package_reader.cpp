#include "ballistic.graphics.io.material_package_reader.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.itexture.h"

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		namespace io {

			material_package_reader::material_package_reader (idevice * device) : _device (device) {}

			const char * material_package_reader::type () const {
				return "material";
			}

			void material_package_reader::load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container) {

				const char * name = element->Attribute ("name");
				const char * effect_name = element->Attribute ("effect");
				
				imaterial * material = _device->create_material (text_to_id (name));

				if (effect_name) {
					ieffect * effect = container [text_to_id (effect_name)];
					material->effect (effect);
				}
				
				auto * cursor = element->FirstAttribute ();
				
				while (cursor) {

					if (strcmp (cursor->Name (), "texture") == 0) {
						itexture * texture = container [text_to_id (cursor->Value ())];
						material->texture (texture);
					} else {
						id_t property_id = text_to_id (cursor->Name ());

						if (material->properties.contains (property_id))
							material->properties [property_id].property->parse (cursor);
						else {
							debug_print ("unrequested graphics material property \"" << cursor->Name () << "\". value not set");
						}

					}

					//if (strcmp (cursor->Name (), "diffuse") == 0) {
					//	color tmp;
					//	color::parse (cursor, tmp);
					//	material->diffuse (tmp);
					//} else if (strcmp (cursor->Name (), "specular") == 0) {
					//	color tmp;
					//	color::parse (cursor, tmp);
					//	material->specular (tmp);
					//} else if (strcmp (cursor->Name (), "opaque") == 0) {
					//	material->opaque (convert_to < bool > (cursor->Value()));
					//} else if (strcmp (cursor->Name (), "effect") == 0) {
					//	ieffect * effect = container [text_to_id (cursor->Value ())];
					//	material->effect (effect);
					//} else if (strcmp (cursor->Name (), "texture") == 0) {
					//	itexture * texture = container [text_to_id (cursor->Value ())];
					//	material->texture (texture);
					//}
				
					cursor = cursor->Next ();
				}
				
				container.add_to_level (material);
			}

		}
	}
}