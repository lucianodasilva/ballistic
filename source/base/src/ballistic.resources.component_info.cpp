#include "ballistic.resources.component_info.h"
#include "ballistic.debug.h"
#include "ballistic.icomponent.h"
#include "ballistic.resources.component_constructor.h"

namespace ballistic {
	namespace resources {
	
		icomponent_constructor * component_info::get_constructor () {
			return _constructor;
		}
		
		void component_info::set_constructor( icomponent_constructor * ctor ) {
			_constructor = ctor;
		}
		
		vector < attribute > & component_info::get_attributes() {
			return _attributes;
		}
		
		icomponent * component_info::create () {
			if (!_constructor) {
				debug_error ("Component constructor not set. Cannot build contructor.");
				return nullptr;
			}
			
			icomponent * new_component = _constructor->create ();
			new_component->setup (_attributes);
			
			return new_component;
		}
		
	}
}