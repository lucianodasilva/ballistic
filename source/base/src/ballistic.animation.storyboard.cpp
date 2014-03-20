#include "ballistic.animation.storyboard.h"

#include "ballistic.animation.ianimation.h"

namespace ballistic {
	namespace animation {

		void storyboard::add_segment (
			real start,
			real duration,
			repeat_mode repeat,
			ifunction * anim
		){
			_animation_segments.push_back (
				storyboard_segment (start, duration, repeat, anim)
			);
		}

		storyboard::storyboard (id_t id) :
			iresource (id)
		{}

		storyboard::~storyboard () {
			for (auto anim : _animation_segments)
				delete anim.function;
		}

		void storyboard::update (real animation_time) {

			for (auto anim : _animation_segments)
				anim.update (animation_time);
		}

	}
}