#ifndef	_ballistic_desktop_frontend_windows_h_
#define _ballistic_desktop_frontend_windows_h_

#include <ballistic.base.h>
#include "ballistic.ifrontend.h"
#include "ballistic.ui.common.h"

#ifdef BALLISTIC_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <windowsx.h>

#undef near
#undef far

namespace ballistic {
	namespace desktop {

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
				ui::mouse_event_type m_event,
				const vec2 & position,
				ui::mouse_button buttons,
				int wheel_delta
			);

			static void send_mouse_message (ui::mouse_event_type m_event, HWND hWnd, WPARAM wParam,LPARAM lParam);

			virtual bool create ();
			virtual void destroy ();

		public:

			// implement ifrontend
			virtual void show ();
			virtual void close ();

			virtual void run ();
			// -------------------

			frontend (game & game_ref, const point & client_size);
			virtual ~frontend ();

			virtual void update ();

			HWND get_handle ();
		};

	}
}

#endif
#endif