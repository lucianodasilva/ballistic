#include "ballistic.entity_factory.h"

namespace ballistic {
		
	atomic < uint32 > entity_factory::_current_id (1);
		
	entity_factory::entity_definition_map entity_factory::_definitions;
		
	entity_definition & entity_factory::define ( const string & name ) {
			
		entity_definition * new_def = new entity_definition (name);
			
		_definitions [hash < string > ()(name)] = new_def;
			
		return *new_def;
	}
		
	entity * entity_factory::create (const string & type ) {
		return create (hash < string > () (type));
	}
		
	entity * entity_factory::create (entity_type_t type) {
			
		uint32 id = _current_id++;
			
		entity * new_entity = new entity (id);
		entity_definition * def = _definitions [type];
			
		entity_definition::iterator
			it = def->begin (),
			end = def->end ();
			
		for (; it != end; ++it) {
			new_entity->add_component (
				component_factory::create (*it)
			);
		}
			
		return new_entity;
	}

}