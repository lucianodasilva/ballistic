//
//  ballistic.ifrontend.h
//  ballistic
//
//  Created by Luciano da Silva on 10/12/14.
//
//

#ifndef ballistic_ballistic_ifrontend_h
#define ballistic_ballistic_ifrontend_h

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
		virtual bool create () = 0;
		virtual void destroy () = 0;
		
		virtual void show () = 0;
		virtual void close () = 0;
		
		virtual void update () = 0;
		
		virtual void do_event_loop (game * game_inst) = 0;
		
	};
	
}

#endif
