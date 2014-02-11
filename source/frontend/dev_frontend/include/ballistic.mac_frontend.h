#ifndef	_ballistic_mac_frontend_h_
#define _ballistic_mac_frontend_h_

#include <ballistic.base.h>

#ifdef BALLISTIC_OS_DARWIN

#include <GL/glew.h>

namespace ballistic {
	namespace mac_desktop {

		class frontend : public ballistic::ifrontend {
		private:
			point _window_client_size;
			
			static ballistic::igame * _game;
			
			static void update_frame ();
			
		public:

			virtual point get_client_size ();

			frontend (const point & client_size);
			virtual ~frontend ();

			virtual bool create ();

			virtual void show ();
			virtual void destroy ();
			
			virtual void update ( ballistic::igame * game );

			virtual void do_event_loop ( ballistic::igame * game );
			
		};

	}
}

#endif
#endif