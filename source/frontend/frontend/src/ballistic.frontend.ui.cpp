#include "ballistic.frontend.ui.h"
#include "ballistic.frontend.defines.h"

namespace ballistic {
	namespace frontend {

		const id_t ui::component_id = text_to_id ("ui");

		ui::ui () : overlay () {}

		void ui::setup (entity * parent, ballistic::containers::property_container & parameters) {
			component::setup (parent, parameters);

			parent->game ().global_notifier.attach (
				{
					id::frontend::on_mouse_event,
					id::message::render_overlay
				},
				this
			);
		}

		void ui::terminate () {
			overlay::terminate ();
			overlay::parent ()->game ().global_notifier.detach (
				{
					id::frontend::on_mouse_event,
					id::message::render_overlay
				},
				this
			);
		}

		void ui::notify (entity * sender, ballistic::message & message) {
		
			id_t message_id = message.id ();

			// handle mouse events
			if (message_id == id::frontend::on_mouse_event) {
				auto event_type = (mouse_event_type)message [id::frontend::mouse_event_type].as < uint32_t > ();

				switch (event_type) {
				case (mouse_event_move) :
					on_mouse_move (message [id::frontend::mouse_position]);
					break;
				case (mouse_event_down) :
					on_mouse_down ({
						message [id::frontend::mouse_position],
						(mouse_button)message [id::frontend::mouse_buttons].as < uint32_t > ()
					});
					break;
				case (mouse_event_up) :
					on_mouse_up ({
						message [id::frontend::mouse_position],
						(mouse_button)message [id::frontend::mouse_buttons].as < uint32_t > ()
					});
					break;
				}


			}
		
		}

	}
}