#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include "ballistic.id.h"
#include "ballistic.containers.notify_property_container.h"
#include "ballistic.containers.component_container.h"
#include "ballistic.message_notifier.h"

using namespace std;

namespace ballistic {

	class game;
	class entity_type;

	class entity {
	private:

		id_t					_id;
		entity_type *			_type;
		ballistic::game &		_game;

	public:

		// avoid copy and assignment
		entity (const entity & orig) = delete;
		entity & operator = (const entity & orig) = delete;

		message_notifier local_notifier;

		containers::notify_property_container properties;
		containers::component_container components;

		id_t id ();
		inline game & game () { return _game; }

		entity_type * type ();
			
		entity ( ballistic::game & game_inst, id_t id_v, entity_type * type_v );

		void kill ();
		
	};
	
}

#endif