#include "ballistic.icomponent.h"
#include "ballistic.entity_model.icomponent_type.h"

#include "ballistic.debug.h"
#include "ballistic.igame.h"


#include <string>

using namespace std;

namespace ballistic {

	icomponent::~icomponent () {}

	entity * component::get_entity () const {
		return _entity;
	}

	igame * component::get_game () const {
		return _game;
	}

	component::component () : _entity (nullptr), _game (nullptr) {}

	void component::setup ( entity * parent ) {
		_game = parent->get_game ();
		_entity = parent;
	}
		
	void component::setup (entity * parent, property_container & parameters) {
		component::setup (parent);
	}

	icomponent * component::create (entity * parent, const res_id_t & id) {
		return create (parent, id.get_id ());
	}

	icomponent * component::create (entity * parent, id_t id) {

		auto ctor = dynamic_cast <entity_model::icomponent_type *> (parent->get_game ()->get_resource (id));

		if (ctor)
			return ctor->create (parent);
		else {
			debug_print ("[base::game::create_component] Unable to load component constructor with id: " << id);
			return nullptr;
		}
	}

	icomponent * component::create (entity * parent, id_t id, property_container & parameters) {
		auto ctor = dynamic_cast <entity_model::icomponent_type *> (parent->get_game ()->get_resource (id));

		if (ctor)
			return ctor->create (parent, parameters);
		else {
			debug_print ("[base::game::create_component] Unable to load component constructor with id: " << id);
			return nullptr;
		}
	}


}