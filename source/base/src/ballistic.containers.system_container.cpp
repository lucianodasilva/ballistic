#include "ballistic.containers.system_container.h"

#include "ballistic.debug.h"
#include "ballistic.isystem.h"

namespace ballistic {

	namespace containers {

		system_container::~system_container () {
			for (auto it_pair : data) {
				delete it_pair.second;
			}
		}

		isystem * system_container::attach (isystem * sys) {

			if (!sys) {
				debug_print ("sys argument set to null");
				return nullptr;
			}

			auto it = data.find (sys->id ());

			if (it != data.end ()) {
				debug_print ("system with id " << sys->id () << " already attached.");
				return nullptr;
			}

			data [sys->id ()] = sys;

			sys->attach ();

			return sys;
		}

		isystem * system_container::detach (id_t id) {
			auto it = data.find (id);

			if (it == data.end ()) {
				debug_print ("system with id " << id << " not attached.");
				return nullptr;
			}

			it->second->detach ();

			data.erase (it);

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


}

