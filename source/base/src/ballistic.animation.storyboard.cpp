#include "ballistic.animation.storyboard.h"

#include "ballistic.animation.ianimation.h"

namespace ballistic {
	namespace animation {

		storyboard::storyboard (id_t id, ianimation * anim) :
			iresource (id),
			_start_time (real ()),
			_animation (anim)
		{}

		storyboard::~storyboard () {
			if (_animation)
				delete _animation;
		}

		real storyboard::start_time () { return _start_time; }

		void storyboard::start_time (const real & v) { _start_time = v; }

		ianimation * storyboard::animation () { return _animation; }

		void storyboard::update (real game_time) {
			if (!_animation)
				return;
			
			real elapsed = game_time - _start_time;
			_animation->update (elapsed);
		}

	}
}