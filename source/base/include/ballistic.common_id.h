#ifndef	_ballistic_common_id_h_
#define _ballistic_common_id_h_

#include "ballistic.id.h"

#define define_id_ext(x,y) \
	const ballistic::id_t x = text_to_id (#y)

#define define_id(x) \
	define_id_ext (x, x)

using namespace std;

namespace ballistic {

	namespace id {

		namespace message {
			define_id_ext (update, message.update);
			define_id_ext (terminate, message.terminate);
			define_id_ext (initialize, message.initialize);
			define_id_ext (property_changed, message.property_changed);
		}

		define_id (null);

		namespace game {
			define_id_ext (game_time, game.game_time);
			define_id_ext (frame_time, game.frame_time);
			define_id_ext (frame_count, game.frame_count);
		}

		// -------------------------------------- 

		define_id (name);
		define_id (id);
		define_id (value);

		define_id (position);
		define_id (rotation);
		define_id (scale);

		define_id (transform);

		define_id (target);
		define_id (up);

		// --------------------------------------
		namespace transformed {
			define_id_ext (id, transformed);
		}

		// --------------------------------------
		// ANIMATION 
		// --------------------------------------
		namespace animation {
			define_id_ext (id, animation);
			define_id_ext (storyboard_id, animation.storyboard_id);
			define_id_ext (start_time, animation.start_time);
			define_id_ext (duration, animation.duration);
			define_id_ext (repeat, animation.repeat);
			define_id_ext (start, animation.start);
			define_id_ext (end, animation.end);
			define_id_ext (control_1, animation.control_1);
			define_id_ext (control_2, animation.control_2);
			define_id_ext (target_id, animation.target_id);
			define_id_ext (repeat_none, animation.repeat_none);
			define_id_ext (repeat_loop, animation.repeat_loop);
			define_id_ext (repeat_reverse, animation.repeat_reverse);
		}

	}
}

#endif