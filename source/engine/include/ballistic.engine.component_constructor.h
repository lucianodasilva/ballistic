#ifndef _ballistic_engine_component_constructor_h_
#define _ballistic_engine_component_constructor_h_

#include "ballistic.engine.icomponent.h"

#include <string>
#include <type_traits>

#define MSG_NOT_COMPONENT_TYPE "Constructor template parameter must be derived from icontructor!"

using namespace std;

namespace ballistic {
	namespace engine {

		class icomponent_constructor {
		public:

			virtual string get_name () = 0;

			virtual icomponent * create () = 0;

		};

		template < class component_t >
		class component_constructor : public icomponent_constructor {
		private:
			static_assert ( is_base_of < icomponent, component_t >::value, MSG_NOT_COMPONENT_TYPE);

			string _name;
		public:

			inline component_constructor ( const string & name ) : _name (name) {}

			virtual inline string get_name () { return _name; }

			virtual icomponent * create () { return new component_t (); }

		};

	}
}

#endif