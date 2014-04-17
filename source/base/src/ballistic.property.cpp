#include "ballistic.property.h"

#include "ballistic.common_id.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	iproperty::iproperty () : p_id (0), p_container (nullptr) {}

	iproperty::iproperty (id_t id_v, entity * container_v) : p_id (id_v), p_container (container_v) {}

	id_t iproperty::id () const { return p_id; }

	entity * iproperty::container () const { return p_container; }

	iproperty::~iproperty () {}

	void iproperty::raise_event () const {
		message m (p_container, id::message::property_changed);
		m [id::id] = p_id;

		p_container->local_notifier.notify (m);
	}

}