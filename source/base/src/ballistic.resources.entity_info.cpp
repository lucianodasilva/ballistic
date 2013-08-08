#include "ballistic.resources.entity_info.h"
#include "ballistic.entity.h"

namespace ballistic {
	namespace resources {

		// property container

		property & entity_info::add_property (id_t id, const var & v) {
			_properties.push_back (property (this, id));

			property & p = _properties.back ();
			p = v;

			return p;
		}

		bool entity_info::has_property (id_t id) {
			for (property & p : _properties)
				if (p.get_id () == id)
					return true;

			return false;
		}

		property & entity_info::get_property (id_t id) {
			for (property & p : _properties) {
				if (p.get_id () == id)
					return p;
			}

			return add_property (id, var ());
		}
		//

		vector < component_info > & entity_info::get_components () {
			return _components;
		}

		entity * entity_info::create (id_t id) {
			
			entity * ent = new entity (id);
			
			for (component_info & comp_info : _components ) {
				ent->add_component(comp_info.create ());
			}
			
			return ent;
		}
		
	}
		
}