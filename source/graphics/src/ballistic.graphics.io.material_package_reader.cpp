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
					} else if (strcmp (cursor->Name (), "specular") == 0) {
						color tmp;
						color::parse (cursor, tmp);
						mat->specular = tmp;
					} else if (strcmp (cursor->Name (), "color_mask") == 0) {
						color tmp;
						color::parse (cursor, tmp);
						mat->color_mask = tmp;
					} else if (strcmp (cursor->Name (), "ambient_sky") == 0) {
						color tmp;
						color::parse (cursor, tmp);
						mat->ambient_sky = tmp;
					} else if (strcmp (cursor->Name (), "ambient_ground") == 0) {
						color tmp;
						color::parse (cursor, tmp);
						mat->ambient_ground = tmp;
					} else if (strcmp (cursor->Name (), "specular_hardness") == 0) {
						mat->specular_hardness = convert_to < real > (cursor->Value ());
					} else if (strcmp (cursor->Name (), "specular_intensity") == 0) {
						mat->specular_intensity = convert_to < real > (cursor->Value ());
					} else if (strcmp (cursor->Name (), "ambient_intensity") == 0) {
						mat->ambient_intensity = convert_to < real > (cursor->Value ());
					} else if (strcmp (cursor->Name (), "blended") == 0) {
						mat->blended = convert_to < bool > (cursor->Value ());
					} else if (strcmp (cursor->Name (), "opacity") == 0) {
						mat->opacity = convert_to < real > (cursor->Value());
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