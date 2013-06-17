#include "ballistic.entity_factory.h"
#include "ballistic.entity.h"

namespace ballistic {
		
	atomic < uint32 > entity_factory::_current_id (1);
		
	entity_factory::entity_definition_map entity_factory::_definitions;
	
	entity_definition & entity_factory::define ( const string & name ) {
		entity_definition & def = _definitions [string_to_id (name)];
		def.set_name (name);
		return def;
	}
	
	entity * entity_factory::create (const string & type ) {
		return create (string_to_id (type));
	}
		
	entity * entity_factory::create (id_t type) {
			
		uint32 id = _current_id++;
			
		entity * new_entity = new entity (id);
		entity_definition & def = _definitions [type];
			
		for (auto & comp_id : def.get_components()) {
			new_entity->create_component(comp_id);
		}
		
		for (auto & att : def.get_attributes()) {
			new_entity->operator[](att.first) = att.second;
		}
		
			
		return new_entity;
	}

}