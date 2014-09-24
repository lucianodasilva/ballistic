#include "ballistic.containers.entity_container.h"

#include "ballistic.debug.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"
#include "ballistic.icomponent.h"

namespace ballistic {
	namespace containers {

		entity_container::entity_container (game * container) {
			data [container->id ()] = container;
		}

		id_t entity_container::reserve_id () {
			id_t new_key = 0;

			do {
				new_key = ++_id_key;
			} while (contains_id (new_key));

			return new_key;
		}

		entity_container::~entity_container () {
			for (auto it_pair : data) {
				if (it_pair.second != &game::instance)
					delete it_pair.second;
			}
		}

		entity * entity_container::create (const res_id_t & entity_type_id) {
			return create (entity_type_id, reserve_id ());
		}

		entity * entity_container::create (const res_id_t & entity_type_id, const id_t & id) {

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
			_new_entities.push_back (ent);

			return ent;
		}

		entity * entity_container::create (const id_t & entity_type_id) {
			return create (entity_type_id, reserve_id ());
		}

		entity * entity_container::create (const id_t & entity_type_id, const id_t & id) {

			entity_type * type = game::instance.resources.get_resource < entity_type > (entity_type_id);

			if (!type) {
				debug_print ("entity type \"" << entity_type_id << "\" not found. no entity created");
				return nullptr;
			}

			if (contains_id (id)) {
				debug_print ("entity with id \"" << id << "\" already exists");
				return nullptr;
			}

			entity * ent = type->create (id);
			_new_entities.push_back (ent);

			return ent;
		}

		void entity_container::kill (entity * instance) {
			_death_row.push_back (instance);
		}

		void entity_container::execute_creates () {
			for (entity * i : _new_entities) {
				i->type ()->setup (i);
				data [i->id ()] = i;
			}

			_new_entities.clear ();
		}

		void entity_container::execute_kills () {
			for (entity * i : _death_row) {
				data.erase (i->id ());
				delete i;
			}

			_death_row.clear ();
		}
	}
}

