#include "ballistic.resources.property_container_reader.h"

#include "ballistic.math.h"

namespace ballistic {
	namespace resources {

		void property_container_reader::read (
			tinyxml2::XMLElement * element,
			ballistic::resources::stack & stack,
			iproperty_container * container
			) {
				tinyxml2::XMLElement * cursor = element->FirstChildElement ();

				while (cursor) {

					var p_val = string (cursor->Value ());

					string prop_type = cursor->Attribute ("type");
					if (!prop_type.empty ()) {
						if (prop_type == "int")
							p_val = p_val.as < int32 > ();
						else if (prop_type == "uint")
							p_val = p_val.as < uint32 > ();
						else if (prop_type == "real")
							p_val = p_val.as < double > ();
						else if (prop_type == "bool")
							p_val = p_val.as < bool > ();
						else if (prop_type == "vec2")
							p_val = p_val.as < vec2 > ();
						else if (prop_type == "vec3")
							p_val = p_val.as < vec3 > ();
						else if (prop_type == "vec4")
							p_val = p_val.as < vec4 > ();
						else if (prop_type == "color")
							p_val = p_val.as < vec4 > ();
						else {
							debug_warn ("[ballistic::resources::property_container_reader::read] Unknown property type \"" << prop_type << "\". No conversion.");
						}
					}

					// add to container
					container->add_property (
						string_to_id (cursor->Name ()),
						p_val
						);

					cursor = cursor->NextSiblingElement ();
				}
			}

	}
}