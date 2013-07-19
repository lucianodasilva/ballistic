#ifndef	_ballistic_entity_constructor_h_
#define _ballistic_entity_constructor_h_

#include <functional>
#include <vector>
#include <string>


#include "ballistic.component_constructor.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.attribute.h"
#include "ballistic.id.h"
#include "ballistic.var.h"

#include <string>
#include <vector>
#include <tinyxml2.h>

using namespace std;

namespace ballistic {
	
	class entity;
	
	class entity_constructor : public resources::iresource {
	private:
		
		string _name;
		
		vector < attribute > _attributes;
		vector < icomponent_constructor * > _components;
		
		void read_attributes ( tinyxml2::XMLElement * attribute_element );
		
	public:

		entity * create ();
		
		static entity_constructor * from_xml ( tinyxml2::XMLElement * );

	};

}


#endif