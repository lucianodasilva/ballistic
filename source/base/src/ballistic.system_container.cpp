#include "ballistic.system_container.h"

#include "ballistic.debug.h"
#include "ballistic.isystem.h"

namespace ballistic {

	system_container::system_container () {}

	system_container::~system_container () {
		for (auto it_pair : _systems) 
		{
			delete it_pair.second;
		}
	}

	isystem * system_container::attach (isystem * sys) {

		if (!sys) {
			debug_print ("sys argument set to null");
			return nullptr;
		}

		auto it = _systems.find (sys->id ());

		if (it != _systems.end ()) {
			debug_print ("system with id " << sys->id () << " already attached.");
			return nullptr;
		}

		_systems [sys->id ()] = sys;

		sys->attach ();

		return sys;
	}

	isystem * system_container::detach (id_t id) {
		auto it = _systems.find (id);

		if (it == _systems.end ()) {
			debug_print ("system with id " << id << " not attached.");
			return nullptr;
		}

		it->second->detach ();

		_systems.erase (it);

		return it->second;
	}

	isystem * system_container::detach (isystem * sys) {
		if (!sys) {
			debug_print ("sys argument set to null");
			return nullptr;
		}

		return detach (sys->id ());
	}


}

