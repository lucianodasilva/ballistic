#ifndef	_ballistic_engine_entity_definition_h_
#define _ballistic_engine_entity_definition_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.engine.component_constructor.h"

using namespace std;

namespace ballistic {
	namespace engine {

		class entity_definition {	
		private:

			string _name;
			vector < component_id_t > _components;

		public:
			
			typedef vector < component_id_t >::iterator iterator;
			
			iterator begin ();
			iterator end ();

			entity_definition ( const string & name );
			
			string & get_name () const;
			
			entity_definition const & operator << (const string & component_name );
			
		};

	}
}

#endif