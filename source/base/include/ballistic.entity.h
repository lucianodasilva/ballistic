#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include <vector>

#include "ballistic.icomponent.h"
#include "ballistic.id.h"
#include "ballistic.property_container.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {

	class game;

	class entity : public property_container {
	private:

		game *					_game;
		id_t					_id;
		vector < icomponent * > _components;

		entity ( const entity & orig );
		entity & operator = ( const entity & orig );

	public:

		virtual void property_changed_event (const property & p);
			
		game * get_game ();
		void set_game (game * g);

		id_t get_id ();
			
		void add_component ( icomponent * component );

		virtual void notify ( ballistic::message & message );

		entity ( id_t id );
		virtual ~entity ();
		
	};
	
}

#endif