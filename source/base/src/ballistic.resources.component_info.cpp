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

		// property container

		property & component_info::add_property (id_t id, const var & v) {
			_properties.push_back (property (this, id));

			property & p = _properties.back ();
			p = v;

			return p;
		}

		bool component_info::has_property (id_t id) {
			for (property & p : _properties)
				if (p.get_id () == id)
					return true;

			return false;
		}

		property & component_info::get_property (id_t id) {
			for (property & p : _properties) {
				if (p.get_id () == id)
					return p;
			}

			return add_property (id, var());
		}
		//
		
		icomponent * component_info::create () {
			if (!_constructor) {
				debug_error ("Component constructor not set. Cannot build contructor.");
				return nullptr;
			}
			
			icomponent * new_component = _constructor->create ();
			new_component->setup (_properties);
			
			return new_component;
		}
		
	}
}