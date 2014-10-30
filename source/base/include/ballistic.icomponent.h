
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_

#include "ballistic.message_notifier.h"
#include "ballistic.game.h"

#include <vector>

namespace ballistic {

	class entity;
	
	template < class component_t >
	class component_constructor;

	class icomponent : public imessage_listener {
	public:

		virtual ballistic::entity *	parent () const = 0;

		virtual ~icomponent ();

		virtual void setup (ballistic::entity * parent_v, containers::property_container & parameters, ballistic::game & game_inst ) = 0;
		
		virtual void terminate () = 0;

	};

}

#endif
