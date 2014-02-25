#include "ballistic.property.h"

#include "ballistic.common_id.h"
#include "ballistic.entity.h"

namespace ballistic {

	iproperty::iproperty () : _id (0), _container (nullptr) {}

	id_t iproperty::id () const { return _id; }

	entity * iproperty::container () const { return _container; }

	iproperty::~iproperty () {}

	void iproperty::raise_event () const {
		if (_container) {

			message m (id::message_property_changed, _container);
			m [id::id] = _id;

			_container->game ()->send_message (m);
		} 
		debug_run ( else {
			debug_print ("changed property with unset container");
		})
	}

}