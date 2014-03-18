#ifndef _ballistic_animation_storyboard_h_
#define _ballistic_animation_storyboard_h_

#include "ballistic.config.h"
#include "ballistic.iresource.h"

namespace ballistic {
	namespace animation {

		class storyboard : public iresource {

		public:

			storyboard (id_t id);

			void update (real game_time, real frame_time);

		};

	}
}

#endif