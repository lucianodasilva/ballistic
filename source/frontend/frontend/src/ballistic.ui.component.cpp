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

		const id_t component::component_id = id::ui::id;

		component::component () : 
			ballistic::component (),
			_renderer (_draw),
			_material (id::null),
			_system (nullptr),
			_layer (nullptr),
			_control (nullptr)
		{
			_material.opaque = false;
		}

		void component::require_properties (entity_type * new_type, component_info & info) {
			new_type->properties
				.require < uint8_t > (id::visual::layer, 0)
				.require < control * > (id::ui::control, nullptr);
		}

		void component::setup (ballistic::containers::property_container & parameters) {
			ballistic::component::setup (parameters);

			ballistic::game & g = game ();
			ballistic::entity & p = ballistic::component::parent ();

			g.global_notifier.attach (
				{
					id::ui::on_mouse_event,
					id::message::render
				},
				this
			);

			_system = dynamic_cast <graphics::graphics_system *> (g.systems [ballistic::id::graphics::system]);
			_layer = p.properties.aquire < uint8_t > (id::visual::layer);
			_control = p.properties.aquire < control * > (id::ui::control);

			_draw.device (_system->device ());
			_draw.overlay_effect (_system->overlay_effect ());
		}

		void component::terminate () {
			ballistic::component::terminate ();
			game ().global_notifier.detach (
				{
					id::ui::on_mouse_event,
					id::message::render
				},
				this
			);
		}

		void component::notify (entity * sender, ballistic::message & message) {

			control * ci = *_control;

			if (!ci)
				return;
		
			id_t message_id = message.id ();

			// handle mouse events
			if (message_id == id::message::render) {
				_renderer.root (ci);
				if (_system)
					_system->push_overlay_item (&_material, &_renderer, *_layer, mat4 ());
			} else 
			if (message_id == id::ui::on_mouse_event) {

				_renderer.root (ci);

				mouse_event_type event_type = (mouse_event_type)message [id::ui::mouse_event_type];

				switch (event_type) {
				case (mouse_event_move) :
					ci->on_mouse_move (message [id::ui::mouse_position]);
					break;
				case (mouse_event_down) :
					ci->on_mouse_down ({
						message [id::ui::mouse_position],
						message [id::ui::mouse_buttons].as < mouse_button > ()
					});
					break;
				case (mouse_event_up) :
					ci->on_mouse_up ({
						message [id::ui::mouse_position],
						message [id::ui::mouse_buttons].as < mouse_button > ()
					});
					break;
				}


			}
		
		}

	}
}