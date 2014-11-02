#include "ballistic.ui.component.h"
#include "ballistic.ui.common.h"

namespace ballistic {
	namespace ui {

		uint8_t component::layer () const {
			if (_layer)
				return *_layer;
			else
				return 0;
		}

		uint8_t component::layer (uint8_t v) {
			if (_layer) {
				*_layer = v;
				return v;
			} else
				return 0;
		}

		const id_t component::component_id = text_to_id ("ui");

		component::component () : 
			ballistic::component (),
			_layer (nullptr)
		{}

		void component::require_properties (entity_type * new_type, component_info & info) {
			new_type->properties
				.require < uint8_t > (id::visual::layer, 0);
		}

		void component::setup (ballistic::containers::property_container & parameters) {
			ballistic::component::setup (parameters);

			ballistic::game & g = game ();
			ballistic::entity & p = ballistic::component::parent ();

			g.global_notifier.attach (
				{
					id::ui::on_mouse_event,
					id::message::render_overlay
				},
				this
			);

			_system = dynamic_cast <graphics::graphics_system *> (g.systems [ballistic::id::graphics::system]);
			_layer = p.properties.aquire < uint8_t > (id::visual::layer);
		}

		void component::terminate () {
			ballistic::component::terminate ();
			game ().global_notifier.detach (
				{
					id::ui::on_mouse_event,
					id::message::render_overlay
				},
				this
			);
		}

		void component::notify (entity * sender, ballistic::message & message) {
		
			id_t message_id = message.id ();

			// handle mouse events
			if (message_id == id::message::render_overlay) {
				if (_system)
					_system->push_overlay_item (nullptr, nullptr, *_layer, mat4 ());
			} else 
			if (message_id == id::ui::on_mouse_event) {
				auto event_type = (mouse_event_type)message [id::ui::mouse_event_type].as < uint32_t > ();

				switch (event_type) {
				case (mouse_event_move) :
					on_mouse_move (message [id::ui::mouse_position]);
					break;
				case (mouse_event_down) :
					on_mouse_down ({
						message [id::ui::mouse_position],
						(mouse_button)message [id::ui::mouse_buttons].as < uint32_t > ()
					});
					break;
				case (mouse_event_up) :
					on_mouse_up ({
						message [id::ui::mouse_position],
						(mouse_button)message [id::ui::mouse_buttons].as < uint32_t > ()
					});
					break;
				}


			}
		
		}

	}
}