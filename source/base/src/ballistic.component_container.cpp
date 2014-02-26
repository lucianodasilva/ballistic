#include "ballistic.component_container.h"

#include "ballistic.debug.h"
#include "ballistic.icomponent.h"

namespace ballistic {

	component_container::~component_container () {
		for (icomponent * c : _components) {
			c->terminate ();
			delete c;
		}
	}

	icomponent * component_container::create () {

	}


}

