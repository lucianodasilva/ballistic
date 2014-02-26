
#ifndef _ballistic_component_container_h_
#define _ballistic_component_container_h_

#include "ballistic.config.h"
#include "ballistic.message.h"

#include <vector>

namespace ballistic {

	class icomponent;
	class entity;

	class component_container : public inotification_target {
	private:
		entity *				_container;
		vector < icomponent * > _components;
	public:

		component_container (entity * container);
		virtual ~component_container ();

		component_container (const component_container & o) = delete;
		component_container & operator = (const component_container & o) = delete;

		virtual icomponent * create (/* add setup info */);

	};
}

#endif
