#include <Windows.h>
#include <iostream>
#include "ballistic.win_desktop.frontend.h"

int main () {

	ballistic::win_desktop::frontend window_instance (point (800, 600));

	if (!window_instance.create ()) {
		std::cout << "Failed to create frontend window!";
		return -1;
	}

	window_instance.show ();

	return 0;
}