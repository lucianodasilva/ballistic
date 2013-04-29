#include "ballistic.engine.entity_definition.h"
#include "ballistic.engine.component_factory.h"

namespace ballistic {
	namespace engine {
		
		iterator entity_definition::begin () {
			return _components.begin ();
		}
		
		iterator entity_definition::end () {
			return _components.end ();
		}
		
		entity_definition::entity_definition ( const string & name ) : _name (name) {}
		
		string entity_definition::get_name () {
			return _name;
		}
		
		entity_definition const & operator << (const string & component_name) {
			
			component_id_t id = hash < string > () (component_name);
			
			if (component_factory::contains (id))
				_components.push_back (id);
			else 
				throw "component not found";
			
			return *this;
		}
		
	}
}