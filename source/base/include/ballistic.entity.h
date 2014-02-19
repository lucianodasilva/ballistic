#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include <vector>

#include "ballistic.id.h"
#include "ballistic.message.h"
#include "ballistic.property_container.h"
#include "ballistic.resources.id.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {

	class igame;
	class icomponent;

	class entity {
	private:

		igame *					_game;
		id_t					_id;
		vector < icomponent * > _components;

		entity ( const entity & orig );
		entity & operator = ( const entity & orig );

		message _property_changed_message;

	public:

		callback_property_map properties;

		virtual void property_changed_event (id_t id, const var & value);
			
		igame * get_game ();
		void set_game (igame * g);

		id_t get_id ();
			
		void add_component ( icomponent * component );

		virtual void notify ( ballistic::message & message );

		entity ( id_t id );
		virtual ~entity ();

		static entity * create (ballistic::igame * game, const res_id_t & type);
		static entity * create (ballistic::igame * game, id_t id, const res_id_t & type);
		
	};
	
}

#endif