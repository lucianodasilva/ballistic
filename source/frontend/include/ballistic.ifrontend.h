//
//  ballistic.ifrontend.h
//  ballistic
//
//  Created by Luciano da Silva on 10/12/14.
//
//

#ifndef ballistic_ballistic_ifrontend_h
#define ballistic_ballistic_ifrontend_h

#include <ballistic.graphics.h>

namespace ballistic {
	
	class game;
	
	class ifrontend {
	public:

		virtual ~ifrontend ();
		
		/*
		 create whatever window or whatnot
		 that where to present the visual field
		 of the engine.
		 */
		virtual bool initialize ( game * game_instance, const point & window_size ) = 0;
		virtual void terminate () = 0;

		virtual void do_event_loop () = 0;
		
	};
	
}

#endif
