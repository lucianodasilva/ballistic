#include "ballistic.entity_type.h"
#include "ballistic.entity.h"

namespace ballistic {

	entity_type::entity_type (const id_t & id_v) : iresource (id_v) {}

	entity * entity_type::create ( id_t id ) {
			
		entity * ent = new entity (id, this);
		properties.copy_to (ent->properties);
			
		for (component_info & comp_info : components )
			ent->components.create (comp_info);

		return ent;
	}
		
		
}