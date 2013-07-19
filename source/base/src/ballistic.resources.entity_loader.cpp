//
//  ballistic.resources.entity_loader.cpp
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#include "ballistic.resources.entity_loader.h"
#include "ballistic.entity_constructor.h"

#include <tinyxml2.h>

using namespace tinyxml2;

namespace ballistic {
	namespace resources {
		
		bool entity_loader::handles ( const string & name ) {
			if (name.size () < 4)
				return false;
			
			return name.compare (name.size () - 4, 4, ".xml") == 0;
		}
		
		iresource * entity_loader::load ( istream & source, ballistic::resources::stack & stack ) {
			
			XMLDocument document;
			
			//TODO: handle these errors properly
			if (document.LoadFile(source))
				return nullptr;
			
			auto root = document.FirstChildElement("package");
			
			if (!root)
				return nullptr;
			
			XMLNode * cursor = root->FirstChild();
			while (cursor) {
				if (strcmp (cursor->Value(), "entity") == 0) {
					XMLElement * entity_element = cursor->ToElement();
					string name = entity_element->Attribute("name");
					
					auto ctor = ballistic::entity_constructor::from_xml(cursor);
					stack.add_to_level (name, ctor);
				}
				
				cursor->NextSibling();
			}
			
			return nullptr;
		}
		
	}
}