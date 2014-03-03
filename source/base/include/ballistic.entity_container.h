#ifndef _ballistic_entity_container_h_
#define _ballistic_entity_container_h_

#include <atomic>
#include <map>

#include "ballistic.id.h"
#include "ballistic.entity_type.h"

using namespace std;

namespace ballistic {

	class entity;
	class game;
		
	class entity_container {
	private:

		atomic<unsigned int> _id_key;

		map < id_t, entity * > _entities;

	public:

		entity_container (game * container);

		entity_container (const entity_container & o) = delete;
		entity_container & operator = (const entity_container & o) = delete;

		virtual inline ~entity_container ();

		id_t reserve_id ();

		entity * create (entity_type * type);
		entity * create (id_t id, entity_type * type);

		inline bool contains_id (id_t id) const {
			return _entities.find (id) != _entities.end ();
		}

		inline entity * operator [] (id_t id) {
			auto it = _entities.find (id);

			if (it == _entities.end ()) {
				return nullptr;
			}

			return it->second;
		}

	};

}

#endif