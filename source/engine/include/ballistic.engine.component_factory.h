#ifndef	_ballistic_engine_component_factory_h_
#define _ballistic_engine_component_factory_h_

#include <functional>
#include <map>
#include <string>

#include "ballistic.engine.icomponent.h"
#include "ballistic.engine.component_constructor.h"

namespace ballistic {
	namespace engine {

		typedef size_t component_id_t;

		class component_factory {
		private:

			typedef map < component_id_t, icomponent_constructor * > constructor_map_t;
			static constructor_map_t _constructors;

		public:

			component_factory ();
			virtual ~component_factory ();

			template < class component_t >
			inline static void define ( const string & name );

			inline static bool contains ( const string & name );
			inline static bool contains ( component_id_t id ); 

			inline static icomponent * create ( const string & name );
			inline static icomponent * create ( component_id_t id );

		};

		template < class component_t >
		void component_factory::define ( const string & name ) {
			icomponent_constructor * ctor = new component_constructor < component_t > (name);
			_constructors [hash <string> ()(name)] = ctor;
		}

		bool component_factory::contains ( const string & name ) {
			return contains ( hash < string > ()(name) );
		}

		bool component_factory::contains ( component_id_t id ) {
			return _constructors.find (id) != _constructors.end ();
		}

		icomponent * component_factory::create ( const string & name ) {
			return create ( hash < string >()(name));
		}

		icomponent * component_factory::create ( component_id_t id ) {
			return _constructors [id]->create ();
		}

	}
}
#endif