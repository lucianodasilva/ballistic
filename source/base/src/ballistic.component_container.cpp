#include "ballistic.component_container.h"
#include "ballistic.icomponent.h"

namespace ballistic {

	component_container::~component_container () {
		for (icomponent * c : _components)
			delete c;
	}

	void component_container::add (icomponent * component) {
		if (!component) {
			debug_error ("[base::component_container::add_component] instance of component not set.");
			return;
		}

		_components.push_back (component);
	}

	void component_container::notify (ballistic::message & message) {
		for (icomponent * c : _components)
			c->notify (message);
	}

}

