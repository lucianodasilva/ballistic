#ifndef _ballistic_frontend_defines_h_
#define _ballistic_frontend_defines_h_

#include <ballistic.base.h>

namespace ballistic {

	enum mouse_event_type : uint32_t {
		mouse_event_none,
		mouse_event_move,
		mouse_event_down,
		mouse_event_up,
		mouse_event_wheel
	};

	enum mouse_button : uint32_t {
		mouse_button_none = 0,
		mouse_button_left = 1,
		mouse_button_right = 2,
		mouse_button_middle = 4
	};

	namespace id {
		namespace frontend {

			define_id (on_mouse_event);
			define_id (mouse_event_type);

			define_id (mouse_buttons);
			define_id (mouse_position);
			define_id (mouse_wheel_delta);

		}
	}
}

#endif