#include "ballistic.entity_constructor.h"
#include "ballistic.entity.h"

namespace ballistic {

	vector < attribute > & entity_constructor::get_attributes () {
		return _attributes;
	}

	vector < icomponent_constructor * > & entity_constructor::get_components () {
		return _components;
	}

	entity * entity_constructor::create () {
		return nullptr;
	}
		
}