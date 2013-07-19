#include "ballistic.resources.entity_loader.h"
#include "ballistic.entity_constructor.h"

#include <tinyxml2.h>

using namespace tinyxml2;

namespace ballistic {
	namespace resources {
		
		bool entity_loader::handles (const string & name) {
			if (name.size () < 4)
				return false;
			
			return name.compare (name.size () - 4, 4, ".xml") == 0;
		}
		
		bool entity_loader::load (istream & source, ballistic::resources::stack & stack) {
			
			XMLDocument document;
			
			//TODO: handle these errors properly
			if (document.LoadFile(source))
				return nullptr;
			
			auto root = document.FirstChildElement("package");
			
			if (!root)
				return nullptr;
			
			XMLElement * cursor = root->FirstChildElement();
			while (cursor) {
				if (strcmp (cursor->Name(), "entity_type") == 0) {
					string name = cursor->Attribute("name");
					
					auto ctor = ballistic::entity_constructor::from_xml(cursor, stack);
					stack.add_to_level (name, ctor);
				}
				
				cursor = cursor->NextSiblingElement();
			}
			
			return nullptr;
		}
		
	}
}