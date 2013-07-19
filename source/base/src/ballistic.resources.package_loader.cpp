//
//  ballistic.resources.entity_loader.cpp
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#include "ballistic.resources.package_loader.h"
#include "ballistic.entity_constructor.h"

#include "ballistic.config.h"
#include "ballistic.attribute.h"

#include "ballistic.math.h"

#include <tinyxml2.h>

using namespace tinyxml2;

namespace ballistic {
	namespace resources {
		
		bool package_loader::handles (const string & name) {
			if (name.size () < 4)
				return false;
			
			return name.compare (name.size () - 4, 4, ".xml") == 0;
		}


		void load_attributes (
			tinyxml2::XMLElement * element, 
			ballistic::resources::stack & stack, 
			vector < attribute > & attribute_vector 
		){
			tinyxml2::XMLElement * cursor = element->FirstChildElement ();

			while (cursor) {
				attribute_vector.push_back (attribute (string_to_id (cursor->Name ())));
				attribute & at = attribute_vector.back ();

				string type = cursor->Attribute ("type");
				string value = cursor->Attribute ("value");

				// Convert XML attribute types
				if (type == "int") {
					at = convert_to < int, string > (value);
				} else if (type == "uint") {
					at = convert_to < unsigned int, string > (value);
				} else if (type == "real") {
					at = convert_to < real, string > (value);
				} else if (type == "res") {
					at = stack.get_resource (value);
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

					at = v;
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

					at = v;
				} else {
					//TODO: handle properly
					attribute_vector.pop_back ();
				}

				cursor = cursor->NextSiblingElement ();
			}
		}

		void load_entity (tinyxml2::XMLElement * element, ballistic::resources::stack & stack) {
			string name = element->Attribute ("name");
			
			entity_constructor * ctor = new entity_constructor ();

			tinyxml2::XMLElement * cursor = element->FirstChildElement ();
			while (cursor) {
				if (strcmp (cursor->Name (), "attributes") == 0)
					load_attributes (cursor, stack, ctor->get_attributes ());

				cursor = cursor->NextSiblingElement ();
			}

			stack.add_to_level (name, ctor);
		}
		
		bool package_loader::load (istream & source, ballistic::resources::stack & stack) {
			
			XMLDocument document;
			
			//TODO: handle these errors properly
			if (document.LoadFile(source))
				return nullptr;
			
			auto root = document.FirstChildElement("package");
			
			if (!root)
				return false;
			
			XMLElement * cursor = root->FirstChildElement();
			while (cursor) {
				if (strcmp (cursor->Name (), "entity_type") == 0)
					load_entity (cursor, stack);
				
				cursor = cursor->NextSiblingElement();
			}
			
			return true;
		}
		
	}
}