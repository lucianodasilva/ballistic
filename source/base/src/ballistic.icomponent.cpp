#include "ballistic.icomponent.h"
#include "ballistic.igame.h"
#include "ballistic.resources.component_constructor.h"

using namespace std;

namespace ballistic {
	
	icomponent::~icomponent () {}

	entity * component::get_entity () const {
		return _entity;
	}

	void component::set_entity ( entity * ent ) {
		_entity = ent;
	}

	component::component () : _entity (nullptr) {}

	void component::setup () {}
		
	void component::setup ( vector < property > & parameters ) {}

	icomponent * component::create (ballistic::igame * game, const res_id_t & id) {
		return create (game, id.get_id ());
	}

	icomponent * component::create (ballistic::igame * game, id_t id) {
		auto ctor = dynamic_cast <resources::icomponent_constructor *> (game->get_resource (id));

		if (ctor)
			return ctor->create ();
		else {
			debug_warn ("[ballistic::game::create_component] Unable to load component constructor with id: " << id);
			return nullptr;
		}
	}

	icomponent * component::create (ballistic::igame * game, id_t id, vector < property > & parameters) {
		auto ctor = dynamic_cast <resources::icomponent_constructor *> (game->get_resource (id));

		if (ctor)
			return ctor->create (parameters);
		else {
			debug_warn ("[ballistic::game::create_component] Unable to load component constructor with id: " << id);
			return nullptr;
		}
	}


}