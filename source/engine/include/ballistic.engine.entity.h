#ifndef	_ballistic_engine_entity_h_
#define _ballistic_engine_entity_h_

#include <vector>


#include "ballistic.engine.attribute.h"
#include "ballistic.engine.icomponent.h"
#include "ballistic.engine.component_factory.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {
	namespace engine {

		typedef uint32 entity_id_t;

		class game;

		class entity {
		public:
			typedef size_t entity_attribute_id_t;
			typedef map < attribute::id_t, attribute > entity_attribute_map;
		private:

			game *					_game;
			entity_id_t				_id;
			vector < icomponent * > _components;
			
			entity_attribute_map	_attributes;

		public:
			
			bool has_attribute ( const string & key );
			bool has_attribute ( engine::attribute::id_t id );
			
			engine::attribute & attribute ( const string & key );
			engine::attribute & attribute ( engine::attribute::id_t id );
			
			game * get_game ();
			void set_game (game * g);

			entity_id_t get_id ();
			
			void add_component ( icomponent * component );
			icomponent * create_component ( const string & id );
			icomponent * create_component ( component_id_t id );

			virtual void notify ( ballistic::engine::message & message );

			entity ( entity_id_t id );
			virtual ~entity ();
			
		};
	};
}

#endif