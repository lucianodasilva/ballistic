#include "ballistic.resources.entity_info.h"
#include "ballistic.entity.h"

namespace ballistic {
	namespace resources {

		vector < attribute > & entity_info::get_attributes () {
			return _attributes;
		}

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