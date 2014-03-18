#include "ballistic.animation.component.h"

#include "ballistic.common_id.h"

namespace ballistic {
	namespace animation {

		storyboard * component::storyboard () {
			return _storyboard;
		}

		void component::require_properties (entity_type * new_type, component_info & info) {
			info.properties.require < id_t > (id::storyboard_id, id::null);
		}

		void component::setup (ballistic::entity * parent, ballistic::property_container & parameters) {
			
			id_t storyboard_id = parameters [id::storyboard_id];

			if (storyboard_id != id::null) {
				_storyboard = game::instance.resources [storyboard_id];
				
				if (!_storyboard) {
					debug_print ("storyboard id \"" << storyboard_id << "\" does not evaluate to a loaded storyboard");
				}
			}

			game::instance.global_notifier.attach (id::message_update, this);
		}

		void component::terminate () {
			game::instance.global_notifier.detach (id::message_update, this);
		}

		void component::notify (ballistic::entity * sender, ballistic::message & message) {
			real game_time = message [id::game_time];
			real frame_time = message [id::frame_time];

			if (_storyboard)
				_storyboard->update (game_time, frame_time);
		}

	}
}