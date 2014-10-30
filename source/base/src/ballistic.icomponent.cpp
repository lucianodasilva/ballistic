#include "ballistic.icomponent.h"
#include "ballistic.component.h"

#include "ballistic.debug.h"

#include <string>

using namespace std;

namespace ballistic {

	icomponent::~icomponent () {}

	entity * component::parent () const {
		return _parent;
	}

	component::component () : _parent (nullptr) {}

	void component::setup (entity * parent_v, containers::property_container & parameters, ballistic::game & game_inst) {
		_parent = parent_v;
	}
	
	void component::terminate () {}

}