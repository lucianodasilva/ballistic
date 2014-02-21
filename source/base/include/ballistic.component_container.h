
#ifndef _ballistic_component_container_h_
#define _ballistic_component_container_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"
#include "ballistic.message.h"

#include <vector>

namespace ballistic {

	class icomponent;

	class component_container : public inotification_target {
	private:
		vector < icomponent * > _components;
	public:

		virtual ~component_container ();

		virtual void add (icomponent * component);
		virtual void notify (ballistic::message & message);

	};
}

#endif
