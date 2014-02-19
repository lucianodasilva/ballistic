#include "ballistic.resources.entity_info.h"
#include "ballistic.entity.h"
#include "ballistic.igame.h"

namespace ballistic {
	namespace resources {

		vector < component_info > & entity_info::get_components () {
			return _components;
		}

		entity * entity_info::create (igame * game, id_t id) {
			
			entity * ent = new entity (id);
			game->add_entity (ent);
			
			for (component_info & comp_info : _components ) {
				ent->add_component(
					comp_info.create (ent)
				);
			}

			for (auto & p : properties)
				ent->properties.add (p.first, p.second);

			return ent;
		}
		
	}
		
}