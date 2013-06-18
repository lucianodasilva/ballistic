#ifndef	_ballistic_component_factory_h_
#define _ballistic_component_factory_h_

#include <functional>
#include <map>
#include <string>

#include "ballistic.id.h"
#include "ballistic.component_constructor.h"

namespace ballistic {

	class icomponent;
	class component_factory {
	private:

		typedef map < id_t, icomponent_constructor * > constructor_map_t;
		static constructor_map_t _constructors;

	public:

		component_factory ();
		virtual ~component_factory ();

		template < class component_t >
		inline static void define ( const string & name );

		inline static bool contains ( const string & name );
		inline static bool contains ( id_t id );

		inline static icomponent * create ( const string & name );
		inline static icomponent * create ( id_t id );

	};

	template < class component_t >
	void component_factory::define ( const string & name ) {
		icomponent_constructor * ctor = new component_constructor < component_t > (name);
		_constructors [hash <string> ()(name)] = ctor;
	}

	bool component_factory::contains ( const string & name ) {
		return contains ( string_to_id (name) );
	}

	bool component_factory::contains ( id_t id ) {
		return _constructors.find (id) != _constructors.end ();
	}

	icomponent * component_factory::create ( const string & name ) {
		return create ( string_to_id (name));
	}

	icomponent * component_factory::create ( id_t id ) {
		return _constructors [id]->create ();
	}

}
#endif