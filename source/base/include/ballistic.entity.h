#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include "ballistic.id.h"
#include "ballistic.property_container.h"
#include "ballistic.component_container.h"

using namespace std;

namespace ballistic {

	class game;

	class entity {
	private:

		game *					_game;
		id_t					_id;

	public:

		// avoid copy and assignment
		entity (const entity & orig) = delete;
		entity & operator = (const entity & orig) = delete;

		property_container properties;

		component_container components;

		game * game ();

		id_t id ();
			
		entity ( id_t id_v );
		
	};
	
}

#endif