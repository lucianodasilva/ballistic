
#ifndef _ballistic_containers_component_container_h_
#define _ballistic_containers_component_container_h_

#include "ballistic.config.h"
#include "ballistic.message.h"
#include "ballistic.containers.icontainer.h"
#include "ballistic.component_info.h"

#include <vector>

namespace ballistic {

	class icomponent;
	class entity;

	namespace containers {

		class component_container {
		private:
			entity *				_container;
			vector < icomponent * > _components;
		public:

			component_container (entity * container);
			virtual ~component_container ();

			component_container (const component_container & o) = delete;
			component_container & operator = (const component_container & o) = delete;

			virtual icomponent * create (component_info & info);

		};

	}
}

#endif
