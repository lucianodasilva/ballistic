#include "ballistic.entity_definition.h"
#include "ballistic.component_factory.h"

namespace ballistic {
		
	entity_definition::iterator entity_definition::begin () {
		return _components.begin ();
	}
		
	entity_definition::iterator entity_definition::end () {
		return _components.end ();
	}
		
	entity_definition::entity_definition ( const string & name ) : _name (name) {}
		
	const string & entity_definition::get_name () const {
		return _name;
	}
		
	entity_definition & entity_definition::operator << (const string & component_name) {
			
		component_id_t id = hash < string > () (component_name);
			
		if (component_factory::contains (id))
			_components.push_back (id);
		else 
			throw "component not found";
			
		return *this;
	}
		
}