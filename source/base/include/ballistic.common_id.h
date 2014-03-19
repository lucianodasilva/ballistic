#ifndef	_ballistic_common_id_h_
#define _ballistic_common_id_h_

#include "ballistic.id.h"

#define define_id(x) \
	const ballistic::id_t x = text_to_id (#x)

using namespace std;

namespace ballistic {

	namespace id {

		define_id (null);
		define_id (message_update);

		define_id (game_time);
		define_id (frame_time);
		define_id (frame_count);

		// -------------------------------------- 
		define_id (message_terminate);

		// -------------------------------------- 
		define_id (message_initialize);

		// -------------------------------------- 
		define_id (message_property_changed);

		define_id (name);
		define_id (id);
		define_id (value);

		// --------------------------------------
		define_id (transform);
		define_id (position);

		// --------------------------------------
		// ANIMATION 
		// --------------------------------------
		define_id (storyboard_id);
		define_id (start);
		define_id (end);
		define_id (control_1);
		define_id (control_2);
		define_id (target_id);

	}
}

#endif