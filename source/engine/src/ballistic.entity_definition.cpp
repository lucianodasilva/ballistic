#include "ballistic.entity_definition.h"
#include "ballistic.component_factory.h"

namespace ballistic {
		
	const string & entity_definition::get_name () const {
		return _name;
	}
	
	void entity_definition::set_name(const string &name) {
		_name = name;
	}
	
	entity_definition::attribute_vector & entity_definition::get_attributes () { return _attributes; }
		
	entity_definition::component_vector & entity_definition::get_components () { return _components; }
	
	entity_definition & entity_definition::attributes ( attribute_vector && attributes ) {
		_attributes.reserve (_attributes.size () + attributes.size());
		_attributes.insert (_attributes.end (), attributes.begin (), attributes.end());
		
		return *this;
	}
	
	entity_definition & entity_definition::components ( component_vector && components ) {
		_components.reserve (_components.size () + components.size ());
		_components.insert (_components.end (), components.begin (), components.end ());
		
		return *this;
	}
		
}