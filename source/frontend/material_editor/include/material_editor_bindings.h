#pragma once
#ifndef	_material_editor_bindings_h_
#define _material_editor_bindings_h_

#include "material_editor_defines.h"

EXPORT int get_ballistic_version ();

using callback_func = void (int important_data);

EXPORT void yada_callback (callback_func func);
			 
#endif