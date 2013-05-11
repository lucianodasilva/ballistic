#include "ballistic.icomponent.h"

namespace ballistic {

	entity & icomponent::get_entity () const {
		return *_entity;
	}

	void icomponent::set_entity ( entity * ent ) {
		_entity = ent;
	}

	icomponent::icomponent () : _entity (nullptr) {}
	icomponent::~icomponent () {}
		
	void icomponent::setup () {}


}