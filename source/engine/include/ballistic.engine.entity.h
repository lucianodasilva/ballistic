#ifndef	_ballistic_engine_entity_h_
#define _ballistic_engine_entity_h_

#include <vector>

#include "ballistic.engine.icomponent.h"

using namespace std;

namespace ballistic {
	namespace engine {

		typedef uint32 entity_id_t;

		class entity {	
		private:

			entity_id_t _id;
			vector < icomponent * > _components;

		public:
			
			entity_id_t get_id ();
			
			void add_component ( icomponent * component );
			virtual void notify ( ballistic::engine::message & message );

			entity ( entity_id_t id );
			~entity ();
			
		};
	};
}

#endif