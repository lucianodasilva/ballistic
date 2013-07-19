#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include <vector>

#include "ballistic.attribute.h"
#include "ballistic.icomponent.h"
#include "ballistic.id.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {

	class game;

	class entity {
	private:

		game *					_game;
		id_t					_id;
		vector < icomponent * > _components;
			
		attribute_map_t	_attributes;

		entity ( const entity & orig );
		entity & operator = ( const entity & orig );

	public:
			
		bool has_attribute ( const string & key );
		bool has_attribute ( id_t id );
			
		attribute & operator [] ( const string & key );
		attribute & operator [] ( id_t id );
			
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