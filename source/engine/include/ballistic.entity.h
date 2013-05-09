#ifndef	_ballistic_entity_h_
#define _ballistic_entity_h_

#include <vector>


#include "ballistic.attribute.h"
#include "ballistic.icomponent.h"
#include "ballistic.component_factory.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {

	class game;

	class entity {
	public:

		typedef uint32 id_t;

		typedef map < attribute::id_t, attribute > entity_attribute_map;
	private:

		game *					_game;
		id_t					_id;
		vector < icomponent * > _components;
			
		entity_attribute_map	_attributes;

		entity ( const entity & orig );
		entity & operator = ( const entity & orig );

	public:
			
		bool has_attribute ( const string & key );
		bool has_attribute ( attribute::id_t id );
			
		attribute & operator [] ( const string & key );
		attribute & operator [] ( attribute::id_t id );
			
		game * get_game ();
		void set_game (game * g);

		id_t get_id ();
			
		void add_component ( icomponent * component );
		icomponent * create_component ( const string & id );
		icomponent * create_component ( component_id_t id );

		virtual void notify ( ballistic::message & message );

		entity ( id_t id );
		virtual ~entity ();
			
	};
}

#endif