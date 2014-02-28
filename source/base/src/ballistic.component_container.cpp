#include "ballistic.component_container.h"

#include "ballistic.debug.h"
#include "ballistic.icomponent.h"

namespace ballistic {

	component_container::component_container (entity * cont) : _container (cont) {}

	component_container::~component_container () {
		for (icomponent * c : _components) {
			c->terminate ();
			delete c;
		}
	}

	icomponent * component_container::create (component_info & info) {
		icomponent * new_comp = info.create (_container);

		if (new_comp)
			_components.push_back (new_comp);

		return new_comp;
	}


}

