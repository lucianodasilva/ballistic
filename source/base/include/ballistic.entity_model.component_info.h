
#ifndef _ballistic_entity_model_component_info_h_
#define _ballistic_entity_model_component_info_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"
#include "ballistic.resources.iresource.h"

#include "ballistic.entity_model.icomponent_type.h"

namespace ballistic {

	class entity;
	class icomponent;

	namespace entity_model {

		class component_info : public resources::iresource {
		private:
			icomponent_type * _type;
		public:

			component_info ();

			icomponent_type * get_type ();
			void set_type (icomponent_type * type);

			property_map properties;

			icomponent * create (entity * parent);

		};

	}
}

#endif
