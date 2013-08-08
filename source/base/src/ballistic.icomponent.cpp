#include "ballistic.icomponent.h"

using namespace std;

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
		
	void component::setup ( vector < property > & parameters ) {}


}