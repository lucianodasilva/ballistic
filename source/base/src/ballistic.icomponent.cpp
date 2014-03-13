#include "ballistic.icomponent.h"

#include "ballistic.debug.h"

#include <string>

using namespace std;

namespace ballistic {

	icomponent::~icomponent () {}

	entity * component::container () const {
		return _container;
	}

	component::component () : _container (nullptr) {}

	void component::setup (entity * container_v, property_container & parameters) {
		_container = container_v;
	}
	
	void component::terminate () {}

}