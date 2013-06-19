#include <Windows.h>
#include <iostream>
#include "ballistic.win_desktop.frontend.h"

#include <ballistic.base.h>

#ifdef BALLISTIC_DESKTOP_WIN_GL
	#include <ballistic.graphics.opengl.h>
	ballistic::graphics::opengl_device device;
#else
	
#endif

int main () {

	ballistic::win_desktop::frontend window_instance (point (800, 640));

	if (!window_instance.create ()) {
		std::cout << "Failed to create frontend window!";
		return -1;
	}

	window_instance.show ();

	ballistic::game game_instance;

	device.set_clear_color (color (.0, .6, 1., 1.));

	game_instance.on_initialize ();
	while (game_instance.frame (&window_instance)) {
		device.clear ();
		device.begin_frame ();

		device.end_frame ();
	}

	return 0;
}