#include "ballistic.icomponent.h"
#include "ballistic.component.h"
#include "ballistic.game.h"

#include "ballistic.debug.h"

#include <string>

using namespace std;

namespace ballistic {

	icomponent::icomponent () : _parent (nullptr) {}
	icomponent::~icomponent () {}

	entity & icomponent::parent () const {
		return *_parent;
	}

	game & icomponent::game () const {
		return *_game;
	}

	component::component () : icomponent () {}

	void component::setup (containers::property_container & parameters) {}
	
	void component::terminate () {}

}