#include "ballistic.property_map.h"
#include "ballistic.entity.h"

namespace ballistic {

	property_map::property_map () : _container (&details::null_property_container::static_instance) {}

	property_map::property_map (iproperty_container * container) : _container (container) {}
	
	property_map::~property_map () {
		for (auto & pair : _properties) {
			if (pair.second)
				delete pair.second;
		}
	}

	void property_map::remove (id_t id) {
		auto it = _properties.find (id);

		if (it != _properties.end ())
			_properties.erase (it);
	}

	bool property_map::contains (id_t id) const {
		return _properties.find (id) != _properties.end ();
	}

	property_map::iterator property_map::begin () {
		return _properties.begin ();
	}

	property_map::iterator property_map::end () {
		return _properties.end ();
	}

}