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
			delete it_pair.second;
		}
	}

	entity * entity_container::create (entity_type * type) {
		if (!type) {
			debug_print ("entity type null. no entity created");
			return nullptr;
		}

		entity * ent = type->create (reserve_id ());
		
		_entities [ent->id ()] = ent;

		return ent;
	}

	entity * entity_container::create (id_t id, entity_type * type) {
		if (!type) {
			debug_print ("entity type null. no entity created");
			return nullptr;
		}

		if (contains_id (id)) {
			debug_print ("entity with id " << id << " already exists");
			return nullptr;
		}

		entity * ent = type->create (id);
		_entities [id] = ent;
		return ent;
	}


}

