#include "ballistic.engine.component_factory.h"

namespace ballistic {
	namespace engine {

		// implement static variable
		map < component_factory::component_id_t, icomponent_constructor * > component_factory::_constructors;

	}
}