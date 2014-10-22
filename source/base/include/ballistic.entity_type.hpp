#ifndef	_ballistic_entity_type_hpp_
#define _ballistic_entity_type_hpp_

#include "ballistic.debug.h"
#include "ballistic.game.h"

#include <vector>

namespace ballistic {

	template < class ... component_types >
	entity_type * entity_type::declare (game & game_ref, const id_t & id) {
		using namespace std;
		auto instance = entity_type::create_instance (game_ref, id);

		struct constructor_handle {
			icomponent_constructor * ctor;
			id_t id;
		};

		vector < constructor_handle > ctors = {{game_ref.resources [component_types::component_id], component_types::component_id} ...};

		for (auto handle : ctors) {
			if (!handle.ctor) {
				debug_error ("no constructor found for component " << handle.id);
				continue;
			}

			instance->components.push_back (component_info ());
			component_info & new_info = instance->components.back ();

			handle.ctor->require_properties (instance, new_info);
			new_info.ctor (handle.ctor);
		}

		return instance;
	}

}


#endif