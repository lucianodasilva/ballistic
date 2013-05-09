#ifndef	_ballistic_entity_definition_h_
#define _ballistic_entity_definition_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.component_factory.h"

using namespace std;

namespace ballistic {

	class entity_definition {	
	private:

		string _name;
		vector < component_id_t > _components;

	public:
			
		typedef vector < component_id_t >::iterator iterator;
			
		iterator begin ();
		iterator end ();

		entity_definition ( const string & name );
			
		const string & get_name () const;
			
		entity_definition & operator << (const string & component_name );
			
	};
}

#endif