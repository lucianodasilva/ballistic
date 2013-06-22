#include "ballistic.win_frontend.h"

#ifdef BALLISTIC_WIN

#ifdef BALLISTIC_DESKTOP_GL
#	include <GL/glew.h>
#endif

namespace ballistic {
	namespace win_desktop {

		LRESULT CALLBACK frontend::message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
			switch ( msg )
			{
				case WM_DESTROY:
					PostQuitMessage(0);
					return 0;
			}
			
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		point frontend::get_client_size () { return _window_client_size; }

		frontend::frontend (const point & client_size ) : _window_client_size (client_size) {
		}

		frontend::~frontend () {}

		bool frontend::create () {

			HINSTANCE h_instance = GetModuleHandle(NULL);
			
			WNDCLASS wc;
			wc.style			= CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc		= message_proc;
			wc.cbClsExtra		= 0;
			wc.cbWndExtra		= 0;
			wc.hInstance		= h_instance;
			wc.hIcon			= LoadIcon (0, IDI_APPLICATION);
			wc.hCursor			= LoadCursor (0, IDC_ARROW);
			wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszMenuName		= 0;
			wc.lpszClassName	= "BallisticWndClass";

			if (!RegisterClass (&wc)) {
				// Failed. TODO: insert super logging here
				return false;
			}

			_window_handle = CreateWindow(
				"BallisticWndClass",
				"Ballistic Win32 Window",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				_window_client_size.x,
				_window_client_size.y,
				0,
				0,
				h_instance,
				0);

			if ( _window_handle == 0 ) {
				// Failed again. TODO: insert super logging here
				return false;
			}

#			ifdef BALLISTIC_DESKTOP_GL //--------------------------------------

				PIXELFORMATDESCRIPTOR pfd = {
					sizeof (PIXELFORMATDESCRIPTOR),
					1, // version number
					PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
					PFD_TYPE_RGBA,
					24, // color depth
					0, 0, 0, 0, 0, 0,
					0, 
					0,
					0,
					0, 0, 0, 0,
					32, // 32 bit z buffer
					0,	// no stencil buffer
					0,
					PFD_MAIN_PLANE,
					0, 
					0, 0, 0
				};

				_window_dc = GetDC (_window_handle);

				int pixel_format = ChoosePixelFormat (_window_dc, & pfd); 
				if (pixel_format == 0) {
					// Failed. TODO: insert super logging here
					return false;
				}

				if (SetPixelFormat (_window_dc, pixel_format, &pfd) == FALSE) {
					// Failed. TODO: insert logging here
					return false;
				}

				_window_gl_rc = wglCreateContext (_window_dc);
				if (_window_gl_rc == NULL) 
					return false;

				if (wglMakeCurrent (_window_dc, _window_gl_rc) == NULL)
					return false;

				glViewport(0, 0, 1024, 700);

#			endif // --------------------------------------------------------------

			return true;
		}

		void frontend::show () {
			ShowWindow (_window_handle, SW_SHOW);
		}

		void frontend::destroy () {
			DestroyWindow (_window_handle);
		}

		void frontend::update (ballistic::game * game) {
			// Process windows events ------------------------------------
			MSG msg;
			while(PeekMessage(&msg, _window_handle, 0, 0, PM_REMOVE) > 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// -----------------------------------------------------------
			// TODO: Fire all input events into the message system here
			// -----------------------------------------------------------
#			ifdef BALLISTIC_DESKTOP_GL
				SwapBuffers (_window_dc);
#			endif
		}

		void frontend::do_event_loop (ballistic::game * game) {
			while (game->frame ()) {
				update (game);
			}
		}

		HWND frontend::get_window_handle () { return _window_handle; }
	}
}
#endif