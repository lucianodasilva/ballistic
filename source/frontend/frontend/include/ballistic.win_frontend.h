#ifndef	_ballistic_win_frontend_h_
#define _ballistic_win_frontend_h_

#include <ballistic.base.h>

#ifdef BALLISTIC_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <windowsx.h>

#undef near
#undef far

namespace ballistic {
	namespace win_desktop {

		class frontend : public ballistic::ifrontend {
		private:

			message
				_on_mouse_up_message,
				_on_mouse_down_message,
				_on_mouse_move_message;

			point	_window_client_size;
			HWND	_window_handle;

#			ifdef BALLISTIC_DESKTOP_GL
				 HDC _window_dc;
				 HGLRC _window_gl_rc;
#			endif

			static LRESULT CALLBACK message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

			void on_resize ();
			void on_mouse_move (const point & p);
			void on_mouse_down (const point & p, int button);
			void on_mouse_up (const point & p, int button);

		public:

			virtual point get_client_size ();

			frontend (const point & client_size);
			virtual ~frontend ();

			virtual bool create ();

			virtual void show ();
			virtual void destroy ();

			virtual void update ();

			virtual void do_event_loop ();

			HWND get_window_handle ();
		};

	}
}

#endif
#endif