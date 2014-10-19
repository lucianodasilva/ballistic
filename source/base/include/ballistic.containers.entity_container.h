#ifndef _ballistic_containers_entity_container_h_
#define _ballistic_containers_entity_container_h_

#include <atomic>
#include <map>

#include "ballistic.id.h"
#include "ballistic.entity_type.h"
#include "ballistic.res_id.h"
#include "ballistic.containers.icontainer.h"

using namespace std;

namespace ballistic {

	class entity;
	class game;

#ifdef _ballistic_game_h_
#define cenas
#endif

	namespace containers {

		class entity_container : public icontainer < map < id_t, entity * > > {
		private:

			atomic<unsigned int>	_id_key;

			vector < entity * >		_new_entities;
			vector < entity * >		_death_row;

			ballistic::game &		_container;

		public:

			entity_container (ballistic::game & container);

			virtual ~entity_container ();

			id_t reserve_id ();

			entity * create (const res_id_t & entity_type_id);
			entity * create (const res_id_t & entity_type_id, const id_t & id);

			entity * create (const id_t & entity_type_id);
			entity * create (const id_t & entity_type_id, const id_t & id);

			void kill (entity * inst);

			void execute_creates ();
			void execute_kills ();

			inline bool contains_id (id_t id) const {
				return data.find (id) != data.end ();
			}

			inline entity * operator [] (id_t id) {
				auto it = data.find (id);

				if (it == data.end ()) {
					return nullptr;
				}

				return it->second;
			}

		};
	}
}

#endif