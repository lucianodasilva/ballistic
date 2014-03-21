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
	class component_info;
		
	class icomponent_constructor : public iresource {
	public:

		icomponent_constructor (const id_t & id);

		virtual inline ~icomponent_constructor (){}

		virtual void require_properties (entity_type * new_entity_type, component_info & info) = 0;

		virtual icomponent * create (entity * parent, property_container & parameters ) = 0;

	};

	namespace details {

		template < class T >
		struct component_has_requirements {
		private:
			typedef char one;
			typedef long two;

			template < class C > static inline one test (decltype (C::require_properties));
			template < class C > static inline two test (...);
		public:
			enum { value = sizeof (test <T> (0)) == sizeof (char) };
		};

		template < class T, bool has_requirements = component_has_requirements < T >::value >
		struct component_require_properties {
			inline static void require (entity_type * new_entity_type, component_info & info) {
				T::require_properties (new_entity_type, info);
			}
		};

		template < class T >
		struct component_require_properties < T, false > {
			inline static void require (entity_type * new_entity_type, component_info & info) {}
		};

	}

	template < class component_t >
	class component_constructor : public icomponent_constructor {
		static_assert ( is_base_of < icomponent, component_t >::value, "component constructor can only refer to classes derived from icomponent");
	public:

		inline component_constructor (const id_t & id) :
			icomponent_constructor (id)
		{}

		inline virtual void require_properties (entity_type * new_entity_type, component_info & info) {
			details::component_require_properties < component_t >::require (new_entity_type, info);
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