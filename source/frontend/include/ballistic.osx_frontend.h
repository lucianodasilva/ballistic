#ifndef	_ballistic_osx_frontend_h_
#define _ballistic_osx_frontend_h_

#include <ballistic.base.h>

#ifdef BALLISTIC_OS_DARWIN

#include "ballistic.ifrontend.h"
#include "ballistic.osx_frontend_native.h"

namespace ballistic {
	namespace osx_desktop {
		
		class frontend : public ballistic::ifrontend {
		private:
			
			NSWindow *
				_window_instance;
			ballistic_window_controller *
				_window_controller;
			
			game *
				_game_instance;
			
		public:
		
			frontend ( );
			virtual ~frontend ();

			virtual bool initialize (game * game_instance, const point & window_size );
			virtual void terminate ();
						
			virtual void do_event_loop ();
			
		};
	
	}
}

#endif
#endif