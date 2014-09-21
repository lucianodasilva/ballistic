#include "ballistic.animation.component.h"

#include "ballistic.common_id.h"
#include "ballistic.animation.driver.h"

namespace ballistic {
	namespace animation {

		const id_t component::component_id = id::animation;

		component::component () : _start_time (-1) {}

		storyboard * component::storyboard () {
			return _storyboard;
		}

		std::vector < idriver * > & component::drivers () {
			return _drivers;
		}

		void component::require_properties (entity_type * new_type, component_info & info) {
			info.properties.require < id_t > (id::storyboard_id, id::null);
		}

		void component::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
			ballistic::component::setup (parent, parameters);
			
			id_t storyboard_id = parameters [id::storyboard_id];

			if (storyboard_id != id::null) {
				_storyboard = game::instance.resources [storyboard_id];
				
				if (!_storyboard) {
					debug_print ("storyboard id \"" << storyboard_id << "\" does not evaluate to a loaded storyboard");
					return;
				}
			}

			// attach animation drivers
			_storyboard->create_drivers (this);
			game::instance.global_notifier.attach (id::message::update, this);
		}

		void component::terminate () {

			// delete animation drivers
			for (auto d : _drivers)
				delete d;

			game::instance.global_notifier.detach (id::message::update, this);
		}

		void component::notify (ballistic::entity * sender, ballistic::message & message) {

			real game_time = message [id::game_time];

			if (_start_time < 0)
				_start_time = game_time;

			real animation_time = game_time - _start_time;

			for (auto drv : _drivers) {
				drv->update (animation_time);
			}
		}

	}
}