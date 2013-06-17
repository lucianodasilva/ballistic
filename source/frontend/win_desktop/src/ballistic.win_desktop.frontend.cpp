#include "ballistic.win_desktop.frontend.h"

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

			return true;
		}

		void frontend::show () {
			ShowWindow (_window_handle, SW_SHOW);
		}

		void frontend::destroy () {
			DestroyWindow (_window_handle);
		}

		void frontend::update (ballistic::game * game) {

		}
	}
}