#ifndef _ballistic_resource_property_container_reader_h_
#define _ballistic_resource_property_container_reader_h_

#include "ballistic.convert.h"
#include "ballistic.property.h"
#include "ballistic.resources.stack.h"
#include "ballistic.math.h"

#include <string>
#include <tinyxml2.h>

namespace ballistic {
	namespace resources {;

		struct property_container_reader {

			typedef void (*property_type_reader_t)(
				const string & type,
				const string & value,
				ballistic::resources::stack & stack,
				var & out_value
			);

			static inline void default_type_reader (
				const string & type,
				const string & value,
				ballistic::resources::stack & stack,
				var & out_value
				) {

					// Convert XML attribute types
					if (type == "int") {
						out_value = convert_to < int, const string > (value);
					} else if (type == "uint") {
						out_value = convert_to < unsigned int, const string > (value);
					} else if (type == "real") {
						out_value = convert_to < real, const string > (value);
					} else if (type == "res") {
						out_value = stack.get_resource (value);
					} else if (type == "vec3") {
						vec3 v;

						stringstream ss (value);
						string trim;

						getline (ss, trim, ',');
						v.x = convert_to < real, string > (trim);
						getline (ss, trim, ',');
						v.y = convert_to < real, string > (trim);
						getline (ss, trim, ',');
						v.z = convert_to < real, string > (trim);

						out_value = v;
					} else if (type == "color" || type == "vec4") {
						vec4 v;

						stringstream ss (value);
						string trim;

						getline (ss, trim, ',');
						v.x = convert_to < real, string > (trim);
						getline (ss, trim, ',');
						v.y = convert_to < real, string > (trim);
						getline (ss, trim, ',');
						v.z = convert_to < real, string > (trim);
						getline (ss, trim, ',');
						v.w = convert_to < real, string > (trim);

						out_value = v;
					} else {
						out_value = value; //as string
					}
			}

			template < 
				property_type_reader_t type_reader
			>
			static inline void read (
				tinyxml2::XMLElement * element,
				ballistic::resources::stack & stack,
				iproperty_container * container
				) {
					tinyxml2::XMLElement * cursor = element->FirstChildElement ();

					while (cursor) {

						var p_val;

						type_reader (
							cursor->Attribute ("type"), 
							cursor->Attribute ("value"), 
							stack, 
							p_val
						);

						// add to container
						container->add_property (
							string_to_id (cursor->Name ()),
							p_val
							);

						cursor = cursor->NextSiblingElement ();
					}
			}


		};
		
	}
}

#endif
