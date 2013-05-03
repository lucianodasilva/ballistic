#ifndef	_ballistic_engine_entity_h_
#define _ballistic_engine_entity_h_

#include <vector>

#include "ballistic.engine.icomponent.h"
#include "ballistic.engine.component_factory.h"

using namespace std;

namespace ballistic {
	namespace engine {

		typedef uint32 entity_id_t;

		class game;

		class entity {	
		private:

			game *					_game;
			entity_id_t				_id;
			vector < icomponent * > _components;

		public:
			
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