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

	void component::setup ( ballistic::entity * container_v ) {
		_container = container_v;
	}
		
	void component::setup (entity * container_v, property_container & parameters) {
		component::setup (container_v);
	}
	
	void component::terminate () {}

}