#include "ballistic.entity_type.h"
#include "ballistic.entity.h"

namespace ballistic {

	entity * entity_type::create ( id_t id ) {
			
		entity * ent = new entity (id, this);
			
		for (component_info & comp_info : components )
			ent->components.create (comp_info);

		// fill entity with properties
		for (auto & p : properties)
			ent->properties.require (p.first, p.second);

		return ent;
	}
		
		
}