#ifndef _ballistic_resources_component_constructor_h_
#define _ballistic_resources_component_constructor_h_

#include <string>
#include <type_traits>

#include "ballistic.icomponent.h"
#include "ballistic.resources.iresource.h"

#define MSG_NOT_COMPONENT_TYPE "Constructor template parameter must be derived from icontructor!"

using namespace std;

namespace ballistic {

	class entity;

namespace resources {
		
		class icomponent_constructor : public resources::iresource {
		public:

			virtual inline ~icomponent_constructor (){}

			virtual icomponent * create (entity * parent) = 0;
			virtual icomponent * create (entity * parent, property_container & parameters ) = 0;

		};

		template < class component_t >
		class component_constructor : public icomponent_constructor {
		private:
			static_assert ( is_base_of < icomponent, component_t >::value, MSG_NOT_COMPONENT_TYPE);
		public:

			virtual icomponent * create (entity * parent) {
				icomponent * new_comp = new component_t ();
				new_comp->setup (parent);
				return new_comp;
			}

			virtual icomponent * create (entity * parent, property_container & parameters)
			{
				icomponent * new_comp = new component_t ();
				new_comp->setup (parent, parameters);
				return new_comp;
			}

		};
	
	}

}

#undef MSG_NOT_COMPONENT_TYPE

#endif