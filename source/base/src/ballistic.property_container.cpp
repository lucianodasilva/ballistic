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

	size_t property_container::count () const {
		return _properties.size ();
	}

	property_container::iterator property_container::begin () {
		return _properties.begin ();
	}

	property_container::iterator property_container::end () {
		return _properties.end ();
	}

	property_container::const_iterator property_container::cbegin () const {
		return _properties.cbegin ();
	}

	property_container::const_iterator property_container::cend () const {
		return _properties.cend ();
	}

	void property_container::copy_to (property_container & dest) const {
		for (auto it : _properties) {
			dest._properties [it.first] = it.second->clone ();
		}
	}

}