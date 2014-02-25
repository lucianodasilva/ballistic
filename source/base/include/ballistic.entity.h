#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include "ballistic.id.h"
#include "ballistic.property_container.h"
#include "ballistic.component_container.h"
#include "ballistic.message_notifier.h"

using namespace std;

namespace ballistic {

	class game;

	class entity {
	private:

		id_t					_id;

	public:

		// avoid copy and assignment
		entity (const entity & orig) = delete;
		entity & operator = (const entity & orig) = delete;

		message_notifier local_notifier;

		property_container properties;

		component_container components;

		id_t id ();
			
		entity ( id_t id_v );
		
	};
	
}

#endif