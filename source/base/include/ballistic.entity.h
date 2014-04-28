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

	public:

		// avoid copy and assignment
		entity (const entity & orig) = delete;
		entity & operator = (const entity & orig) = delete;

		message_notifier local_notifier;

		containers::notify_property_container properties;
		containers::component_container components;

		id_t id ();

		entity_type * type ();
			
		entity ( id_t id_v, entity_type * type_v );

		void kill ();
		
	};
	
}

#endif