#ifndef	_ballistic_win_frontend_h_
#define _ballistic_win_frontend_h_

#include <ballistic.base.h>
#include "ballistic.frontend.defines.h"

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

			game & _game;

			message
				_on_mouse_message;

			point	_window_client_size;
			HWND	_window_handle;

#			ifdef BALLISTIC_DESKTOP_GL
				 HDC _window_dc;
				 HGLRC _window_gl_rc;
#			endif

			static LRESULT CALLBACK message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

			void on_resize ();
			void on_mouse_event (
				mouse_event_type m_event,
				const point & position,
				mouse_button buttons,
				int wheel_delta
			);

			static void send_mouse_message (mouse_event_type m_event, HWND hWnd, WPARAM wParam,LPARAM lParam);

		public:

			virtual point get_client_size ();

			frontend (game & game_ref, const point & client_size);
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