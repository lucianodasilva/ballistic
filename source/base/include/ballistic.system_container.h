#ifndef _ballistic_system_container_h_
#define _ballistic_system_container_h_

using namespace std;

#include <map>

#include "ballistic.id.h"

namespace ballistic {

	class isystem;
		
	class system_container {
	private:

		map < id_t, isystem * > _systems;

	public:

		system_container (const system_container & o) = delete;
		system_container & operator = (const system_container & o) = delete;

		system_container ();
		virtual inline ~system_container ();

		isystem * attach (isystem * sys);

		isystem * detach (id_t id);
		isystem * detach (isystem * sys);

		inline bool contains_system (id_t id) const {
			return _systems.find (id) != _systems.end ();
		}

		inline isystem * operator [] (id_t id) {
			auto it = _systems.find (id);

			if (it == _systems.end ()) {
				return nullptr;
			}

			return it->second;
		}

	};

}

#endif