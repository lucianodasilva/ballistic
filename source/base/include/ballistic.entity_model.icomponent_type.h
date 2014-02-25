
#ifndef _ballistic_entity_model_icomponent_type_h_
#define _ballistic_entity_model_icomponent_type_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"
#include "ballistic.resources.iresource.h"

#include "ballistic.icomponent.h"

namespace ballistic {

	class entity;

	namespace entity_model {

		class icomponent_type : public resources::iresource {
		public:

			virtual ~icomponent_type ();

			virtual icomponent * create (entity * parent) = 0;
			virtual icomponent * create (entity * parent, property_container & parameters) = 0;

		};

		template < class component_t >
		class component_type : public icomponent_type {
		private:
			static_assert (is_base_of < icomponent, component_t >::value, "Component type template parameter must be derived from icontructor!");
		public:

			virtual icomponent * create (entity * parent) {
				icomponent * new_comp = new component_t ();
				
				new_comp->setup (parent);
				return new_comp;
			}

			virtual icomponent * create (entity * parent, property_container & parameters) {
				icomponent * new_comp = new component_t ();

				new_comp->setup (parent, parameters);
				return new_comp;
			}

		};

	}
}

#endif
