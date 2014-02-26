#include "ballistic.property.h"

#include "ballistic.common_id.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	iproperty::iproperty () : _id (0), _container (nullptr) {}

	iproperty::iproperty (id_t id_v, entity * container_v) : _id (id_v), _container (container_v) {}

	id_t iproperty::id () const { return _id; }

	entity * iproperty::container () const { return _container; }

	iproperty::~iproperty () {}

	void iproperty::raise_event () const {
		if (_container) {

			message m (_container, id::message_property_changed);
			m [id::id] = _id;

			_container->local_notifier.notify (m);
		} 
		debug_run ( else {
			debug_print ("changed property with unset container");
		})
	}

}