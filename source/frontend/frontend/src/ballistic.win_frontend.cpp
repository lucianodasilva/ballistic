#include "ballistic.win_frontend.h"
#include "ballistic.frontend.defines.h"

#ifdef BALLISTIC_OS_WINDOWS

#include <GL/glew.h>

namespace ballistic {
	namespace win_desktop {

		void frontend::send_mouse_message (mouse_event_type m_event, HWND hWnd, WPARAM wParam, LPARAM lParam) {

			point pos = {GET_X_LPARAM (lParam), GET_Y_LPARAM (lParam)};

			mouse_button buttons = mouse_button_none;

			buttons = mouse_button (buttons | (wParam & MK_LBUTTON ? mouse_button_left : mouse_button_none));
			buttons = mouse_button (buttons | (wParam & MK_RBUTTON ? mouse_button_right : mouse_button_none));
			buttons = mouse_button (buttons | (wParam & MK_MBUTTON ? mouse_button_middle : mouse_button_none));

			int delta = GET_WHEEL_DELTA_WPARAM (wParam);

			frontend * instance = reinterpret_cast <frontend *> (GetWindowLongPtr (hWnd, GWLP_USERDATA));
			instance->on_mouse_event (m_event, pos, buttons, delta);
		}

		LRESULT CALLBACK frontend::message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

			switch (msg) {
			case WM_CREATE:
			{
				CREATESTRUCT * create = reinterpret_cast <CREATESTRUCT *> (lParam);
				frontend * instance = reinterpret_cast <frontend *> (create->lpCreateParams);
				SetWindowLongPtr (hWnd, GWLP_USERDATA, (LONG_PTR)instance);
				return DefWindowProc (hWnd, msg, wParam, lParam);
			}
			case WM_DESTROY:
				PostQuitMessage (0);
				return 0;
			case WM_SIZE:
			{
				frontend * instance = reinterpret_cast <frontend *> (GetWindowLongPtr (hWnd, GWLP_USERDATA));
				instance->on_resize ();
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				send_mouse_message (mouse_event_move, hWnd, wParam, lParam);
				return 0;
			}
			case WM_LBUTTONDOWN:
			{
				send_mouse_message (mouse_event_down, hWnd, wParam, lParam);
				return 0;
			}
			case WM_LBUTTONUP:
			{
				send_mouse_message (mouse_event_up, hWnd, wParam, lParam);
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				send_mouse_message (mouse_event_down, hWnd, wParam, lParam);
				return 0;
			}
			case WM_RBUTTONUP:
			{
				send_mouse_message (mouse_event_up, hWnd, wParam, lParam);
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				send_mouse_message (mouse_event_wheel, hWnd, wParam, lParam);
				return 0;
			}
			default:
				return DefWindowProc (hWnd, msg, wParam, lParam);
			}
		}

		void frontend::on_resize () {
			RECT client_size = {0};
			GetClientRect (_window_handle, &client_size);

			_window_client_size = {
				client_size.right - client_size.left,
				client_size.bottom - client_size.top
			};

			glViewport (0, 0, _window_client_size.x, _window_client_size.y);
		}

		void frontend::on_mouse_event (
			mouse_event_type m_event,
			const point & position,
			mouse_button buttons,
			int wheel_delta
		) {
			_on_mouse_message [id::frontend::mouse_event_type] = (uint32_t)m_event;
			_on_mouse_message [id::frontend::mouse_position] = position;
			_on_mouse_message [id::frontend::mouse_buttons] = (uint32_t)buttons;
			_on_mouse_message [id::frontend::mouse_wheel_delta] = wheel_delta;

			_game.global_notifier.notify (_on_mouse_message);
		}

		point frontend::get_client_size () { return _window_client_size; }

		frontend::frontend (game & game_ref, const point & client_size) :
			_game (game_ref),
			_window_client_size (client_size),
			_on_mouse_message (id::frontend::on_mouse_event)
		{
			_on_mouse_message.require < point > (id::frontend::mouse_position);
			_on_mouse_message.require < uint32_t > (id::frontend::mouse_buttons);
			_on_mouse_message.require < int > (id::frontend::mouse_wheel_delta);
			_on_mouse_message.require < uint32_t > (id::frontend::mouse_event_type);
		}

		frontend::~frontend () {}

		bool frontend::create () {

			HINSTANCE h_instance = GetModuleHandle (NULL);

			WNDCLASS wc;
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = message_proc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = h_instance;
			wc.hIcon = LoadIcon (0, IDI_APPLICATION);
			wc.hCursor = LoadCursor (0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
			wc.lpszMenuName = 0;
			wc.lpszClassName = "BallisticWndClass";

			if (!RegisterClass (&wc)) {
				debug_error ("[ballistic::win_desktop::frontend::create] Failed to register window class");
				return false;
			}

			_window_handle = CreateWindow (
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
				this);

			if (_window_handle == 0) {
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

			int pixel_format = ChoosePixelFormat (_window_dc, &pfd);
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

			if (wglMakeCurrent (_window_dc, _window_gl_rc) == NULL) {
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
			MSG msg = {};
			while (PeekMessage (&msg, _window_handle, 0, 0, PM_REMOVE) > 0) {
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}
			// -----------------------------------------------------------
			// TODO: Fire all input events into the message system here
			// -----------------------------------------------------------
#			ifdef BALLISTIC_DESKTOP_GL
			SwapBuffers (_window_dc);
#			endif
		}

		void frontend::do_event_loop () {
			while (_game.frame ()) {
				update ();
			}
		}

		HWND frontend::get_window_handle () { return _window_handle; }
	}
}
#endif