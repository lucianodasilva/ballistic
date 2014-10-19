#include "ballistic.entity_type.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	entity_type::entity_type (const id_t & id_v) : iresource (id_v) {}

	entity * entity_type::create (game & game_ref, const id_t & id) {
		entity * instance = new entity (game_ref, id, this);
		properties.setup_container (instance->properties);

		return instance;
	}

	entity * entity_type::setup ( entity * instance ) {
		for (component_info & comp_info : components )
			instance->components.create (comp_info);

		return instance;
	}

	entity_type * entity_type::create_instance (game & game_ref, const id_t & id) {
		entity_type * instance = new entity_type (id);
		game_ref.resources.add_to_global (instance);
		return instance;
	}	
		
}