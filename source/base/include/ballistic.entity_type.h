#ifndef	_ballistic_entity_type_h_
#define _ballistic_entity_type_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.containers.property_definition_container.h"
#include "ballistic.component_info.h"
#include "ballistic.id.h"
#include "ballistic.iresource.h"

#include <string>
#include <vector>

using namespace std;

namespace ballistic {
	
	class entity;
		
	class entity_type : public iresource {	
	private:

		static entity_type * create_instance (const id_t & id);

	public:

		entity_type (const id_t & id_v);

		vector < component_info > components;

		containers::property_definition_container properties;

		entity * create (const id_t & id);
		entity * setup (entity * instance);

		template < class ... component_types >
		inline static entity_type * declare (const id_t & id);

	};

	template < class ... component_types >
	entity_type * entity_type::declare (const id_t & id) {
		auto instance = entity_type::create_instance (id);

		vector < icomponent_constructor * > ctors = { game::instance.resources [component_types::component_id] ...};

		for (auto ctor : ctors) {
			instance->components.push_back (component_info ());
			component_info & new_info = instance->components.back ();

			ctor->require_properties (instance, new_info);
			new_info.ctor (ctor);
		}

		return instance;
	}

}


#endif