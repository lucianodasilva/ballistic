#ifndef _ballistic_animation_storyboard_h_
#define _ballistic_animation_storyboard_h_

#include "ballistic.config.h"
#include "ballistic.iresource.h"
#include "ballistic.property_container.h"

#include <vector>

namespace ballistic {
	namespace animation {

		enum repeat_mode {
			repeat_mode_none,
			repeat_mode_loop,
			repeat_mode_reverse
		};

		class ifunction;
		class idriver;
		class component;

		class storyboard : public iresource {
		public:

			class action {
			private:

				real		_start_time;
				real		_duration;
				repeat_mode _repeat;

				id_t		_target_id;

				ifunction *	_function;

			public:

				static void require_parameters (property_container & parameters);

				action (
					real start_time,
					real duration,
					repeat_mode repeat,
					id_t target_id,
					ifunction * func
				);

				idriver * create_driver (entity * target);

				inline real tween (float animation_time);

			};

		private:

			std::vector < action >	_animation_actions;

		public:

			void add_action (property_container & parameters, ifunction * func);

			void create_drivers (component * instance);

			storyboard (id_t id);
			virtual ~storyboard ();

		};

		real storyboard::action::tween (float animation_time) {

			if (animation_time < _start_time)
				return real (0);

			real t = animation_time - _start_time;

			switch (_repeat) {
			case repeat_mode_loop:
				// kinda sawtooth function
				t = t / _duration;
				t = t - std::floor (t);
				break;
			case repeat_mode_reverse:
				t =	// adapted triangle function
					real (0.63661977236758134307553505349006) // half pi
					* std::asin (
					std::sin (
					(real (6.283185307179586476925286766559) / _duration) * t // 2pi
					)
					) + real (1);
				break;
			default:
				// repeat_mode_none
				t = t / _duration;

				if (t > 1.0)
					t = 1.0;
				break;
			}

			return t;
		}

	}
}

#endif