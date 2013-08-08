#include "ballistic.resources.property_container_reader.h"

#include "ballistic.math.h"

namespace ballistic {
	namespace resources {

		void property_container_reader::read (
			tinyxml2::XMLElement * element,
			ballistic::resources::stack & stack,
			iproperty_container * container
		){
			tinyxml2::XMLElement * cursor = element->FirstChildElement ();

			while (cursor) {

				string type = cursor->Attribute ("type");
				string value = cursor->Attribute ("value");

				var p_val;

				// Convert XML attribute types
				if (type == "int") {
					p_val = convert_to < int, string > (value);
				} else if (type == "uint") {
					p_val = convert_to < unsigned int, string > (value);
				} else if (type == "real") {
					p_val = convert_to < real, string > (value);
				} else if (type == "res") {
					p_val = stack.get_resource (value);
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

					p_val = v;
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

					p_val = v;
				} else {
					p_val = value; //as string
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