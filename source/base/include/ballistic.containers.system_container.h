#ifndef _ballistic_containers_system_container_h_
#define _ballistic_containers_system_container_h_

#include <map>

#include "ballistic.id.h"
#include "ballistic.containers.icontainer.h"

using namespace std;

namespace ballistic {

	class isystem;

	namespace containers {

		class system_container : public icontainer < map < id_t, isystem * > > {
		public:

			virtual ~system_container ();

			isystem * attach (isystem * sys);

			isystem * detach (id_t id);
			isystem * detach (isystem * sys);

			inline bool contains_system (id_t id) const {
				return data.find (id) != data.end ();
			}

			inline isystem * operator [] (id_t id) {
				auto it = data.find (id);

				if (it == data.end ()) {
					return nullptr;
				}

				return it->second;
			}

		};

	}

}

#endif