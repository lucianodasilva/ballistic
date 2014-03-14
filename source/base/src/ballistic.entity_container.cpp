#include "ballistic.entity_container.h"

#include "ballistic.debug.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"
#include "ballistic.icomponent.h"

namespace ballistic {

	entity_container::entity_container (game * container) {
		_entities [container->id ()] = container;
	}

	id_t entity_container::reserve_id () {
		id_t new_key = 0;

		do {
			new_key = ++_id_key;
		} while (contains_id (new_key));

		return new_key;
	}

	entity_container::~entity_container () {
		for (auto it_pair : _entities) 
		{
			if (it_pair.second != &game::instance)
				delete it_pair.second;
		}
	}

	entity * entity_container::create (const res_id_t & entity_type_id) {
		return create (reserve_id (), entity_type_id);
	}

	entity * entity_container::create (const id_t & id, const res_id_t & entity_type_id) {

		entity_type * type = game::instance.resources.get_resource < entity_type > (entity_type_id);

		if (!type) {
			debug_print ("entity type \"" << entity_type_id.id () << "\" not found. no entity created");
			return nullptr;
		}

		if (contains_id (id)) {
			debug_print ("entity with id \"" << id << "\" already exists");
			return nullptr;
		}

		entity * ent = type->create (id);
		_entities [id] = ent;
		return ent;
	}


}

