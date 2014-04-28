#include "ballistic.containers.component_container.h"

#include "ballistic.debug.h"
#include "ballistic.icomponent.h"

namespace ballistic {
	namespace containers {

		component_container::component_container (entity * cont) : _container (cont) {}

		component_container::~component_container () {
			for (icomponent * c : data) {
				c->terminate ();
				delete c;
			}
		}

		icomponent * component_container::create (component_info & info) {
			icomponent * new_comp = info.create (_container);

			if (new_comp)
				data.push_back (new_comp);

			return new_comp;
		}

	}
}

