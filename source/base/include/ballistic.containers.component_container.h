
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

		class component_container : public icontainer < std::vector < icomponent * > > {
		private:
			entity *				_container;
		public:

			component_container (entity & container);
			virtual ~component_container ();

			virtual icomponent * create (component_info & info);

		};

	}
}

#endif
