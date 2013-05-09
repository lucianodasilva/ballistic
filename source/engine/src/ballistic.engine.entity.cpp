#include "ballistic.engine.entity.h"
#include <functional>

namespace ballistic {
	namespace engine {
		
		bool entity::has_attribute(const string &key) {
			return has_attribute(hash < string > () (key));
		}
		
		bool entity::has_attribute(engine::attribute::id_t id) {
			return _attributes.find (id) != _attributes.end ();
		}
		
		attribute & entity::attribute(const string &key) {
			return attribute(hash < string > () (key));
		}
		
		attribute & entity::attribute(engine::attribute::id_t id ) {
			return _attributes [id];
		}

		game * entity::get_game () { return _game; }
		void entity::set_game ( game * g ) { _game = g; }
		
		entity_id_t entity::get_id () { return _id; }
		
		void entity::add_component ( icomponent * component ) {
			component->set_entity (this);
			component->setup ();
			
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