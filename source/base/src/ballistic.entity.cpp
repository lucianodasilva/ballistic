#include "ballistic.entity.h"
#include "ballistic.common_id.h"
#include "ballistic.game.h"
#include "ballistic.resources.entity_info.h"
#include <functional>

namespace ballistic {

	void entity::property_changed_event (const property & p) {
		_property_changed_message.set_sender (this);

		_property_changed_message [id::id] = p.get_id ();
		_property_changed_message [id::value] = p.get_value ();

		this->get_game ()->send_message (_property_changed_message);
	}

	game * entity::get_game () { return _game; }
	void entity::set_game ( game * g ) { _game = g; }
		
	id_t entity::get_id () { return _id; }
		
	void entity::add_component ( icomponent * component ) {
		if (!component) {
			debug_error ("[ballistic::entity::add_component] instance of component not set.");
			return;
		}

		component->set_entity (this);
		_components.push_back (component);
	}

	void entity::notify ( ballistic::message & message ) {
		for ( icomponent * it : _components) {
			it->notify (message);
		}
	}

	entity::entity (id_t id) : _game (nullptr), _id (id), _property_changed_message (id::message_property_changed) {}

	entity::~entity () {
		for ( icomponent * it : _components ) {
			delete it;
		}
	}

	entity * entity::create (ballistic::game * game, const res_id_t & type) {
		return create (game, game->create_id_key (), type);
	}

	entity * entity::create (ballistic::game * game, id_t id, const res_id_t & type) {
		auto ctor = dynamic_cast <resources::entity_info *> (game->get_resource (type));

		if (ctor) {
			entity * ent = ctor->create (id);
			game->add_entity (ent);
			return ent;
		} else {
			debug_warn ("[ballistic::entity::create] Unable to load entity with id: " << type.get_id ());
			return nullptr;
		}
	}

}