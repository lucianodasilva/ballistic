#include "ballistic.engine.entity.h"

namespace ballistic {
	namespace engine {
		
		entity_id_t entity::get_id () { return _id; }
		
		void entity::add_component ( icomponent * component ) {
			_components.push_back (component);
		}

		void entity::notify ( ballistic::engine::message & message ) {
			vector < icomponent * >::iterator
				it = _components.begin (),
				end = _components.end ();

			for (; it != end; ++it) {
				(*it)->notify (message);
			}
		}

		entity::entity ( entity_id_t id ) : _id (id) {}

		entity::~entity () {
			vector < icomponent * >::iterator
				it = _components.begin (),
				end = _components.end ();
			
			for (; it != end; ++it) {
				delete (*it);
			}
		}
		
	}
}