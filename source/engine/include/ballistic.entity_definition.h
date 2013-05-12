#ifndef	_ballistic_entity_definition_h_
#define _ballistic_entity_definition_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.id.h"
#include "ballistic.var.h"

using namespace std;

namespace ballistic {
	
	class entity_factory;

	class entity_definition {
	public:
		
		friend class entity_factory;
		
		typedef vector < pair < id_t, var > > attribute_vector;
		typedef vector < id_t > component_vector;
	private:

		string _name;
		
		attribute_vector _attributes;
		component_vector _components;
		
		void set_name ( const string & name );

	public:
		
		const string & get_name () const;

		attribute_vector & get_attributes ();
		component_vector & get_components ();
		
		entity_definition & attributes ( attribute_vector && attributes );
		entity_definition & components ( component_vector && components );

	};

}

#endif