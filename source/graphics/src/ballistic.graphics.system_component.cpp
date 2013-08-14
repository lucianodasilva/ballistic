#include "ballistic.graphics.system_component.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		system_component::system_component () :
			_render_message (id::message_render) 
		{}

		void system_component::push_item (imaterial * material, imesh * mesh, const mat4 & transform) {}

		void system_component::set_device ( idevice * device ) {
			_device = device;
		}

		idevice * system_component::get_device () {
			return _device;
		}

		void system_component::set_camera (camera cam) {
			_camera = cam;
		}

		const camera & system_component::get_camera () {
			return _camera;
		}

		void system_component::notify ( ballistic::message & message ) {

			if (!_device)
				return;

			if (message.get_id () != ballistic::id::message_update) return;

			// 1st frame - setup stuff
			if (!_game) {
				_game = get_entity ()->get_game ();
				_render_message.set_sender (get_entity ());
				_render_message [graphics::id::system_component] = this;
			}

			// notify entities with visuals
			_game->send_message (_render_message);

			// sort

			_device->clear ();
			_device->begin_frame ();

			// render

			_device->end_frame ();
			_device->present ();
		}

	}
}