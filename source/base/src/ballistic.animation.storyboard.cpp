#include "ballistic.animation.storyboard.h"

#include "ballistic.animation.component.h"
#include "ballistic.animation.driver.h"
#include "ballistic.animation.function.h"

namespace ballistic {
	namespace animation {

		void storyboard::action::require_parameters (containers::property_container & parameters) {
			parameters
				.require < real > (id::start_time, 0)
				.require < real > (id::duration, 0)
				.require < id_t > (id::target_id, id::null)
				.require < id_t > (id::repeat, id::repeat_none);
		}

		storyboard::action::action (
			real start_time,
			real duration,
			repeat_mode repeat,
			id_t target_id,
			ifunction * func
		) :
		_start_time (start_time),
			_duration (duration),
			_repeat (repeat),
			_target_id (target_id),
			_function (func)
		{}

		idriver * storyboard::action::create_driver (entity * target) {
			return _function->create_driver (*this, target, _target_id);
		}

		void storyboard::add_action (
			containers::property_container & parameters,
			ifunction * func
		){
			repeat_mode mode;
			id_t repeat_id = parameters [id::repeat];

			if (repeat_id == id::repeat_none)
				mode = repeat_mode_none;
			else if (repeat_id == id::repeat_loop)
				mode = repeat_mode_loop;
			else if (repeat_id == id::repeat_reverse)
				mode = repeat_mode_reverse;
			else {
				debug_print ("unknown animation repeat mode \"" << repeat_id << "\"");
				mode = repeat_mode_none;
			}

			_animation_actions.push_back (
				action (
					parameters [id::start_time].as < real > (),
					parameters [id::duration].as < real > (),
					mode,
					parameters [id::target_id].as < id_t > (),
					func
				)
			);
		}

		void storyboard::create_drivers (component * instance) {
			for (action & act : _animation_actions)
				instance->drivers ().push_back (act.create_driver (&instance->parent ()));
		}

		storyboard::storyboard (id_t id) :
			iresource (id)
		{}

		storyboard::~storyboard () {}


	}
}