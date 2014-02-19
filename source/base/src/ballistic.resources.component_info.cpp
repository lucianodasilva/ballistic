#include "ballistic.resources.component_info.h"
#include "ballistic.debug.h"
#include "ballistic.icomponent.h"
#include "ballistic.resources.component_constructor.h"

namespace ballistic {
	namespace resources {

		component_info::component_info () : _constructor (nullptr) {}
	
		icomponent_constructor * component_info::get_constructor () {
			return _constructor;
		}
		
		void component_info::set_constructor( icomponent_constructor * ctor ) {
			_constructor = ctor;
		}
		
		icomponent * component_info::create (entity * parent) {
			if (!_constructor) {
				debug_error ("[ballistic::resources::component_info::create] Component constructor not set. Cannot create component instance.");
				return nullptr;
			}
			
			icomponent * new_component = _constructor->create (parent, properties);
			
			return new_component;
		}
		
	}
}