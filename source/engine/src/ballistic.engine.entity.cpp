#include "ballistic.engine.entity.h"
#include <functional>

namespace ballistic {
	namespace engine {

		game * entity::get_game () { return _game; }
		void entity::set_game ( game * g ) { _game = g; }
		
		entity_id_t entity::get_id () { return _id; }
		
		void entity::add_component ( icomponent * component ) {
			component->set_entity (this);
			_components.push_back (component);
		}

		icomponent * entity::create_component ( const string & id ) {
			return create_component (hash < string > ()(id));
		}

		icomponent * entity::create_component ( component_id_t id ) {
			icomponent * new_component = component_factory::create (id);

			add_component (new_component);
			return new_component;
		}

		void entity::notify ( ballistic::engine::message & message ) {
			vector < icomponent * >::iterator
				it = _components.begin (),
				end = _components.end ();

			for (; it != end; ++it) {
				(*it)->notify (message);
			}
		}

		entity::entity ( entity_id_t id ) : _game (nullptr), _id (id) {}

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