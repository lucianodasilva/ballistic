#ifndef _ballistic_animation_driver_h_
#define _ballistic_animation_driver_h_

#include "ballistic.property.h"
#include "ballistic.animation.storyboard.h"

namespace ballistic {
	namespace animation {

		template < class value_t >
		class function;

		class idriver {
		public:

			virtual iproperty * target () = 0;

			virtual void update (real animation_time) = 0;

		};

		template < class value_t >
		class driver : public idriver {
		private:

			property < value_t > *	_target;
			storyboard::action &	_action;

			function < value_t > *	_function;

		public:

			inline driver (
				storyboard::action & act_ref,
				property < value_t > * target,
				function < value_t > * function
			):
				_action (act_ref),
				_target (target),
				_function (function)
			{}

			inline virtual iproperty * target () override { return _target; }

			inline virtual void update (real animation_time) override {
				_function->update (
					_action.tween (animation_time),
					_target
				);
			}

		};


	}
}

#endif