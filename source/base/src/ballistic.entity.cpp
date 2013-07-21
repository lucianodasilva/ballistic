#include "ballistic.entity.h"
#include <functional>

namespace ballistic {

	bool entity::has_attribute(const string &key) {
		return has_attribute(hash < string > () (key));
	}
		
	bool entity::has_attribute(id_t id) {
		return _attributes.find (id) != _attributes.end ();
	}
		
	attribute & entity::operator [](const string &key) {
		return operator [] (hash < string > () (key));
	}
		
	attribute & entity::operator [] (id_t id ) {
		return _attributes [id];
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