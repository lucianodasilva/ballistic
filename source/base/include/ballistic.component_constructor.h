#ifndef _ballistic_component_constructor_h_
#define _ballistic_component_constructor_h_

#include <string>
#include <type_traits>

#include "ballistic.resources.iresource.h"

#define MSG_NOT_COMPONENT_TYPE "Constructor template parameter must be derived from icontructor!"

using namespace std;

namespace ballistic {
	
	class icomponent;

	class icomponent_constructor : public resources::iresource {
	public:

		virtual inline ~icomponent_constructor (){}

		virtual icomponent * create () = 0;

	};

	template < class component_t >
	class component_constructor : public icomponent_constructor {
	private:
		static_assert ( is_base_of < icomponent, component_t >::value, MSG_NOT_COMPONENT_TYPE);
	public:

		virtual icomponent * create () { return new component_t (); }

	};

}

#endif