#include "ballistic.entity.h"
#include "ballistic.common_id.h"
#include "ballistic.game.h"
#include <functional>

namespace ballistic {

	void entity::property_changed_event (const property & p) {
		message m (this, id::message_property_changed);

		m [id::id] = p.get_id();
		m [id::value] = (var)p;

		this->get_game ()->send_message (m);
	}

	game * entity::get_game () { return _game; }
	void entity::set_game ( game * g ) { _game = g; }
		
	id_t entity::get_id () { return _id; }
		
	void entity::add_component ( icomponent * component ) {
		component->set_entity (this);

		_components.push_back (component);
	}

	void entity::notify ( ballistic::message & message ) {
		for ( icomponent * it : _components) {
			it->notify (message);
		}
	}

	entity::entity ( id_t id ) : _game (nullptr), _id (id) {}

	entity::~entity () {
		for ( icomponent * it : _components ) {
			delete it;
		}
	}
		
}