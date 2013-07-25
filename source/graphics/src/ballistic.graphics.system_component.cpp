#include "ballistic.graphics.system_component.h"

namespace ballistic {
	namespace graphics {

		void system_component::push_item () {}

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

			// notify visible items to render
			mat4 view;

			_device->clear ();
			_device->begin_frame ();

			// for each item
			// _device->set_transform (view * item->transform);

			_device->end_frame ();
			_device->present ();
		}

	}
}