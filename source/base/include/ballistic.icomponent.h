
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_

#include "ballistic.message_notifier.h"

#include <vector>

namespace ballistic {

	class entity;
	class game;
	
	template < class component_t >
	class component_constructor;

	class icomponent : public imessage_listener {
	private:
		ballistic::entity * _parent;
		ballistic::game * _game;

		template < class T >
		friend class component_constructor;

	public:

		virtual ballistic::entity &	parent () const;
		virtual ballistic::game & game () const;

		icomponent ();
		virtual ~icomponent ();

		virtual void setup (containers::property_container & parameters) = 0;
		
		virtual void terminate () = 0;

	};

}

#endif
