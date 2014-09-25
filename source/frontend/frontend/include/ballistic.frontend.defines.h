#ifndef _ballistic_frontend_defines_h_
#define _ballistic_frontend_defines_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace id {
		namespace frontend {

			define_id (on_mouse_move);
			define_id (on_mouse_up);
			define_id (on_mouse_down);
			define_id (on_mouse_wheel);

			define_id (mouse_button);
			define_id (mouse_position);
			define_id (mouse_wheel_delta);

		}
	}
}

#endif