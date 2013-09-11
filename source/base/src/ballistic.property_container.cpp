#include "ballistic.property_container.h"

namespace ballistic {

	property_container::~property_container () {
	}

	void property_container::property_changed_event (const property & p) {}

	property & property_container::add_property (id_t id, const var & value) {
		property & p = _property_map [id] = property (this, id);
		p = value;
		return p;
	}

	bool property_container::has_property (id_t id) {
		return _property_map.find (id) != _property_map.end ();
	}

	property & property_container::get_property (id_t id) {
		property_map_t::iterator it = _property_map.find (id);

		if (it == _property_map.end ()) {
			return add_property (id, var ());
		} else
			return it->second;
	}

}