#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include <vector>

#include "ballistic.id.h"
#include "ballistic.message.h"
#include "ballistic.property_map.h"
#include "ballistic.resources.id.h"

#include "ballistic.component_container.h"

using namespace std;

namespace ballistic {

	class igame;

	class entity : public iproperty_container, public inotification_target {
	private:

		igame *					_game;
		id_t					_id;

		entity ( const entity & orig );
		entity & operator = ( const entity & orig );

		message _property_changed_message;

	public:

		property_map properties;

		component_container components;

		virtual void property_changed_event (iproperty * changed_property);
			
		igame * get_game ();
		void set_game (igame * g);

		id_t get_id ();
			
		virtual void notify ( ballistic::message & message );

		entity ( id_t id );

		static entity * create (ballistic::igame * game, const res_id_t & type);
		static entity * create (ballistic::igame * game, id_t id, const res_id_t & type);
		
	};
	
}

#endif