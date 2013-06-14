#ifndef	_ballistic_win_desktop_frontend_h_
#define _ballistic_win_desktop_frontend_h_

#include <ballistic.base.h>

#include <Windows.h>

namespace ballistic {
	namespace win_desktop {

		class frontend : public ballistic::ifrontend {
		private:

			point	_window_client_size;
			HWND	_window_handle;

			static LRESULT CALLBACK message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
			 
		public:

			virtual point get_client_size ();

			frontend (const point & client_size);
			virtual ~frontend ();

			virtual bool create ();

			virtual void show ();
			virtual void destroy ();

		};

	}
}

#endif