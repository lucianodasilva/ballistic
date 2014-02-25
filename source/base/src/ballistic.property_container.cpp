#include "ballistic.property_container.h"
#include "ballistic.entity.h"

namespace ballistic {

	property_container::property_container () : _container (nullptr) {}

	property_container::property_container (entity * container) : _container (container) {}
	
	property_container::~property_container () {
		for (auto & pair : _properties) {
			if (pair.second)
				delete pair.second;
		}
	}

	void property_container::remove (id_t id) {
		auto it = _properties.find (id);

		if (it != _properties.end ())
			_properties.erase (it);
	}

	bool property_container::contains (id_t id) const {
		return _properties.find (id) != _properties.end ();
	}

	property_container::iterator property_container::begin () {
		return _properties.begin ();
	}

	property_container::iterator property_container::end () {
		return _properties.end ();
	}

}