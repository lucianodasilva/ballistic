#include "ballistic.entity_type.h"
#include "ballistic.entity.h"

namespace ballistic {

	entity_type::entity_type (const id_t & id_v) : iresource (id_v) {}

	entity * entity_type::create (const id_t & id) {
		entity * instance = new entity (id, this);
		properties.setup_container (instance->properties);

		return instance;
	}

	entity * entity_type::setup ( entity * instance ) {
		for (component_info & comp_info : components )
			instance->components.create (comp_info);

		return instance;
	}
		
		
}