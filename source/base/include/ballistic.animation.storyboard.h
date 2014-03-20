#ifndef _ballistic_animation_storyboard_h_
#define _ballistic_animation_storyboard_h_

#include "ballistic.config.h"
#include "ballistic.iresource.h"
#include "ballistic.animation.function.h"

#include <vector>

namespace ballistic {
	namespace animation {

		class storyboard_segment {
		private:

			real		_start_time;
			real		_duration;
			repeat_mode _repeat;

		public:

			ifunction * function;

			inline storyboard_segment (
				real start_time,
				real duration,
				repeat_mode repeat,
				ifunction * func
			) :
				_start_time (start_time),
				_duration (duration),
				_repeat (repeat),
				function (func)
			{}

			inline void update (real animation_time) {
				
				if (animation_time < _start_time) {
					function->update (real (0));
					return;
				}

				real tween = animation_time - _start_time;

				switch (_repeat) {
				case repeat_mode_loop:
					// kinda sawtooth function
					tween = tween / _duration;
					std::modf (tween, &tween);
					break;
				case repeat_mode_reverse:
					tween =	// adapted triangle function
						real (0.63661977236758134307553505349006) // half pi
						* std::asin (
						std::sin (
						(real (6.283185307179586476925286766559) / _duration) * tween // 2pi
						)
					) + real (1);
					break;
				default:
					// repeat_mode_none
					tween = tween / _duration;

					if (tween > 1.0)
						tween = 1.0;
					break;
				}

				function->update (tween);
			}

		};

		class storyboard : public iresource {
		private:

			std::vector < storyboard_segment >	
					_animation_segments;

		public:

			void add_segment (real start, real duration, repeat_mode repeat, ifunction * func);

			storyboard (id_t id);
			virtual ~storyboard ();

			void update (real animation_time);

		};

	}
}

#endif