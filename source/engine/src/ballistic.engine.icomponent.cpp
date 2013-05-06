#include "ballistic.engine.icomponent.h"

namespace ballistic {
	namespace engine {

		entity * icomponent::get_entity () const {
			return _entity;
		}

		void icomponent::set_entity ( entity * ent ) {
			_entity = ent;
		}

		icomponent::icomponent () : _entity (nullptr) {}
		icomponent::~icomponent () {}
		
		void setup () {}

	}
}