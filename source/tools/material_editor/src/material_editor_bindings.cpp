#include "material_editor_bindings.h"

int get_ballistic_version () {
	return 3;
}

void yada_callback (callback_func func) {
	func (5);
}