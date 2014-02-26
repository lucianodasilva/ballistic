
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_

#include "ballistic.message_notifier.h"

#include <vector>

namespace ballistic {

	class entity;

	class icomponent : public imessage_listener {
	public:

		virtual ballistic::entity *	container () const = 0;

		virtual ~icomponent ();

		virtual void setup (ballistic::entity * container_v) = 0;
		virtual void setup (ballistic::entity * container_v, property_container & parameters) = 0;
		
		virtual void terminate () = 0;

	};

	// abstract implementation
	class component : public icomponent {
	private:
		ballistic::entity * _container;
	public:

		virtual ballistic::entity * container () const;

		component ();

		virtual void setup (ballistic::entity * container_v);
		virtual void setup (ballistic::entity * container_v, property_container & parameters);
		
		virtual void terminate ();

	};
	
}

#endif
