#include "ballistic.entity_constructor.h"
#include "ballistic.entity.h"

namespace ballistic {

	entity * entity_constructor::create () {
		return nullptr;
	}
	
	void entity_constructor::read_attributes(tinyxml2::XMLElement * attribute_element) {
		tinyxml2::XMLElement * cursor = attribute_element->FirstChildElement();
		
		while (cursor) {
			attribute at (string_to_id(cursor->Name()));
			
			string type = cursor->Attribute("type");
			
			
			
			cursor = cursor->NextSiblingElement();
		}
	}
	
	entity_constructor * entity_constructor::from_xml ( tinyxml2::XMLElement * element ) {
		
		entity_constructor * ctor = new entity_constructor ();
		
		ctor->_name = element->Attribute("name");
		
		tinyxml2::XMLNode * cursor = element->FirstChild();
		while (cursor) {
			if (strcmp (cursor->Value(), "attributes") == 0)
				ctor->read_attributes(cursor->ToElement());
			
			cursor = cursor->NextSibling();
		}
		
		return ctor;
	}
		
}