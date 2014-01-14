#ifndef	_ballistic_win_frontend_h_
#define _ballistic_win_frontend_h_

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include "ifrontend.h"

class frontend : public ifrontend {
private:

	POINT	_window_client_size;
	HWND	_window_handle;

	HDC _window_dc;
	HGLRC _window_gl_rc;

	static LRESULT CALLBACK message_proc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

public:

	frontend (int width, int height);

	virtual ~frontend ();

	virtual bool create ();

	virtual void show ();
	virtual void destroy ();

	virtual void update ();

	virtual void do_event_loop (update_callback callback);

	HWND get_window_handle ();
};

#endif
#endif