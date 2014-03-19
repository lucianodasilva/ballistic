#ifndef _ballistic_animation_storyboard_h_
#define _ballistic_animation_storyboard_h_

#include "ballistic.config.h"
#include "ballistic.iresource.h"

namespace ballistic {
	namespace animation {

		class ianimation;

		class storyboard : public iresource {
		private:

			real			_start_time;
			ianimation 	*	_animation;

		public:

			storyboard (id_t id, ianimation * anim);
			virtual ~storyboard ();

			real start_time ();
			void start_time (const real & v);

			ianimation	* animation ();

			void update (real game_time);

		};

	}
}

#endif