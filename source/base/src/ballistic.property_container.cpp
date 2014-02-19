#include "ballistic.property_container.h"
#include "ballistic.entity.h"

namespace ballistic {

	void property_map::add (id_t id, const var & v) {
		_properties [id] = v;
	}

	void property_map::remove (id_t id) {
		auto it = _properties.find (id);

		if (it != _properties.end ())
			_properties.erase (it);
	}

	bool property_map::contains (id_t id) const {
		return _properties.find (id) != _properties.end ();
	}

	std::map < id_t, var >::iterator property_map::begin () {
		return _properties.begin ();
	}

	std::map < id_t, var >::iterator property_map::end () {
		return _properties.end ();
	}

	callback_property_map::callback_property_map (entity * parent) : _parent (parent) {}

}