#ifndef	_ballistic_mac_frontend_h_
#define _ballistic_mac_frontend_h_

#include <ballistic.base.h>

#ifdef BALLISTIC_OS_DARWIN

#include <GL/glew.h>

namespace ballistic {
	namespace mac_desktop {

		class frontend : public ballistic::ifrontend {
		private:
			
			static game * _game;
			static message _on_mouse_message;
			
			point _window_client_size;
			
			static void update_frame ();
			
			static void on_mouse_button (int button, int state,
								  int x, int y);
			
			static void on_mouse_move (int x, int y);
			
		public:

			virtual point get_client_size ();

			frontend (game & game_ref, const point & client_size);
			
			virtual ~frontend ();

			virtual bool create ();

			virtual void show ();
			virtual void destroy ();
			
			virtual void update ();

			virtual void do_event_loop ();
			
		};
		
		struct view_test {
			
			void show ();
			
		};

	}
}

#endif
#endif