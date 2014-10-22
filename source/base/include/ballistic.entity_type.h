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
	class game;

	class entity_type : public iresource {
	private:

		static entity_type * create_instance (game & game_ref, const id_t & id);

	public:

		entity_type (const id_t & id_v);

		vector < component_info > components;

		containers::property_definition_container properties;

		entity * create (game & game_ref, const id_t & id);
		entity * setup (entity * instance);

		template < class ... component_types >
		inline static entity_type * declare (game & game_ref, const id_t & id);

	};

}

#endif