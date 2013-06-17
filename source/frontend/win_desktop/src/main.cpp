#include <Windows.h>
#include <iostream>
#include "ballistic.win_desktop.frontend.h"

#include <ballistic.base.h>

int main () {

	ballistic::win_desktop::frontend window_instance (point (800, 640));

	if (!window_instance.create ()) {
		std::cout << "Failed to create frontend window!";
		return -1;
	}

	window_instance.show ();

	ballistic::game game_instance;

	game_instance.on_initialize ();
	game_instance.do_loop (&window_instance);

	return 0;
}