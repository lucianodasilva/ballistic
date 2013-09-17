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

					const char * value_ptr = cursor->Attribute ("value");
					if (!value_ptr) {
						debug_error ("[ballistic::resources::property_container_reader::read] Property " << cursor->Name () << " has no value. Property not added!");
					} else {

						string value = value_ptr;
						
						var p_val;

						const char * prop_type_ptr = cursor->Attribute ("type");

						if (prop_type_ptr) {

							string prop_type = prop_type_ptr;

							if (!prop_type.empty ()) {
								if (prop_type == "int")
									p_val = convert_to < int32 > (value);
								else if (prop_type == "uint")
									p_val = convert_to < uint32 > (value);
								else if (prop_type == "real")
									p_val = convert_to < double > (value);
								else if (prop_type == "bool")
									p_val = convert_to < bool > (value);
								else if (prop_type == "vec2") {
									vec2 tmp;
									convert_vectors (value, tmp);
									p_val = tmp;
								} else if (prop_type == "vec3") {
									vec3 tmp;
									convert_vectors (value, tmp);
									p_val = tmp;
								} else if (prop_type == "vec4") {
									vec4 tmp;
									convert_vectors (value, tmp);
									p_val = tmp;
								} else if (prop_type == "color") {
									vec4 tmp;
									convert_vectors (value, tmp);
									p_val = tmp;
								} else if (prop_type == "res")
									p_val = string_to_id (value);
								else {
									debug_warn ("[ballistic::resources::property_container_reader::read] Unknown property type \"" << prop_type << "\". No conversion.");
								}

							}
						} else {
							p_val = value;
						}

						// add to container
						container->add_property (
							string_to_id (cursor->Name ()),
							p_val
							);
					}

					cursor = cursor->NextSiblingElement ();
				}
			}

	}
}