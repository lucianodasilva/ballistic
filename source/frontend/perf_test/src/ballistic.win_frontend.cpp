#include "ballistic.win_frontend.h"

#ifdef BALLISTIC_OS_WINDOWS

#include <GL/glew.h>

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
				debug_error ("[ballistic::win_desktop::frontend::create] Failed to register window class");
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
				debug_error ("[ballistic::win_desktop::frontend::create] Failed to create window instance");
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
					debug_error ("[ballistic::win_desktop::frontend::create] Failed to create pixel format");
					return false;
				}

				if (SetPixelFormat (_window_dc, pixel_format, &pfd) == FALSE) {
					debug_error ("[ballistic::win_desktop::frontend::create] Failed to setS pixel format");
					return false;
				}

				_window_gl_rc = wglCreateContext (_window_dc);
				if (_window_gl_rc == NULL) {
					debug_error ("[ballistic::win_desktop::frontend::create] Failed to create open gl render context");
					return false;
				}

				if (wglMakeCurrent (_window_dc, _window_gl_rc) == NULL) 
				{
					debug_error ("[ballistic::win_desktop::frontend::create] Failed to select open gl render context");
					return false;
				}

				//glViewport (0, 0, 
				//			_window_client_size.x,
				//			_window_client_size.y);

#			endif // --------------------------------------------------------------

			return true;
		}

		void frontend::show () {
			ShowWindow (_window_handle, SW_SHOW);
		}

		void frontend::destroy () {
			DestroyWindow (_window_handle);
		}

		void frontend::update () {
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

		void frontend::do_event_loop () {
			while (game::instance.frame ()) {
				update ();
			}
		}

		HWND frontend::get_window_handle () { return _window_handle; }
	}
}
#endif