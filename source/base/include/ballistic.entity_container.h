#ifndef _ballistic_entity_container_h_
#define _ballistic_entity_container_h_

#include <atomic>
#include <map>

#include "ballistic.id.h"
#include "ballistic.entity_type.h"
#include "ballistic.res_id.h"

using namespace std;

namespace ballistic {

	class entity;
	class game;
		
	class entity_container {
	private:

		atomic<unsigned int> _id_key;

		map < id_t, entity * >	_entities;

		vector < entity * >		_new_entities;
		vector < entity * >		_death_row;

	public:

		entity_container (game * container);

		entity_container (const entity_container & o) = delete;
		entity_container & operator = (const entity_container & o) = delete;

		virtual ~entity_container ();

		id_t reserve_id ();

		entity * create (const res_id_t & entity_type_id);
		entity * create (const id_t & id, const res_id_t & entity_type_id);

		void kill (entity * inst);

		void execute_creates ();
		void execute_kills ();

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