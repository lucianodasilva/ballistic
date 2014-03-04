#ifndef _ballistic_component_constructor_h_
#define _ballistic_component_constructor_h_

#include <string>
#include <type_traits>

#include "ballistic.icomponent.h"
#include "ballistic.iresource.h"

using namespace std;

namespace ballistic {

	class entity;
	class entity_type;
		
	class icomponent_constructor : virtual public iresource {
	public:

		virtual inline ~icomponent_constructor (){}

		virtual void require_properties (entity_type * new_entity_type) = 0;

		virtual icomponent * create (entity * parent) = 0;
		virtual icomponent * create (entity * parent, property_container & parameters ) = 0;

	};

	template < class component_t >
	class component_constructor : virtual public icomponent_constructor {
		static_assert ( is_base_of < icomponent, component_t >::value, "component constructor can only refer to classes derived from icomponent");
	public:

		inline component_constructor (id_t id) :
			iresource (id),
			icomponent_constructor (*this)
		{}

		inline virtual void require_properties (entity_type * new_entity_type) {
			
		}

		inline virtual icomponent * create (entity * parent) {
			icomponent * new_comp = new component_t ();
			new_comp->setup (parent);
			return new_comp;
		}

		inline virtual icomponent * create (entity * parent, property_container & parameters)
		{
			icomponent * new_comp = new component_t ();
			new_comp->setup (parent, parameters);
			return new_comp;
		}

	};
	

}

#endif