#include "ballistic.graphics.system_component.h"

namespace ballistic {
	namespace graphics {

		void system_component::push_item () {}

		void system_component::set_device ( idevice * device ) {
			_device = device;

			_mesh = _device->create_mesh ();

			ballistic::graphics::vertex vbuffer [4]
				= {
					{vec3 (-0.1, 0.1, 0.0), vec2 (0.0, 0.0)},
					{vec3 (0.1, 0.1, 0.0), vec2 (1.0, 0.0)},
					{vec3 (0.1, -0.1, 0.0), vec2 (1.0, 1.0)},
					{vec3 (-0.1, -0.1, 0.0), vec2 (0.0, 1.0)}
			};

			uint16 index [6] = {
				0, 1, 2,
				0, 2, 3
			};

			_mesh->set_data (vbuffer, 4, index, 6);
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
			mat4 model_view;
			mat4 ortho_projection = camera::make_projection (-1., 1., -1., 1., 0, 100);

			_device->clear ();
			_device->begin_frame ();

			_device->set_transform (model_view);
			_device->set_projection (ortho_projection);

			_device->set_current_mesh (_mesh);
			_mesh->render ();

			// for each item
			// _device->set_transform (view * item->transform);

			_device->end_frame ();
			_device->present ();
		}

	}
}