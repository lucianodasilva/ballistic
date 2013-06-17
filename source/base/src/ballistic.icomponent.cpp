#include "ballistic.icomponent.h"

namespace ballistic {
	
	icomponent::~icomponent () {}

	entity & component::get_entity () const {
		return *_entity;
	}

	void component::set_entity ( entity * ent ) {
		_entity = ent;
	}

	component::component () : _entity (nullptr) {}
		
	void component::setup () {}


}