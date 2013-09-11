#include "ballistic.graphics.system_component.h"
#include "ballistic.graphics.common_id.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		system_component::system_component () :
			_device (nullptr),
			_game (nullptr),
			_render_message (id::message_render) 
		{}

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

		void system_component::render () {

			if (!_device) {
				debug_error ("[ballistic::graphics::system_component::render] Graphics device not set!");
				return;
			}

			_render_list.clear ();

			// notify entities with visuals
			_game->send_message (_render_message);

			_device->set_view (_camera.get_view ());

			// sort
			_render_list.sort ();

			_device->clear ();
			_device->begin_frame ();

			// render loop ---------------------------
			uint32 render_count = _render_list.size ();
			imaterial * material = nullptr;
			ieffect * effect = nullptr;
			imesh * mesh = nullptr;

			for (uint32 i = 0; i < render_count; ++i) {
				render_item & item = _render_list [i];

				if (item.material->get_effect () != effect) {
					effect = item.material->get_effect ();
					_device->activate (effect);
				}

				if (item.material != material) {
					material = item.material;
					_device->activate (material);
				}

				if (item.mesh != mesh) {
					mesh = item.mesh;
					_device->activate (mesh);
				}

				// render the stuffs
				_device->draw_active_mesh (item.transform);

			}

			_device->end_frame ();
			_device->present ();
		}

		void system_component::notify ( ballistic::message & message ) {

			if (message.get_id () != ballistic::id::message_update) return;

			// 1st frame - setup stuff
			if (!_game) {
				_game = get_entity ()->get_game ();
				_render_message.set_sender (get_entity ());
				_render_message [graphics::id::system_component] = this;

				if (!_device)
					_device = _game->get_property (graphics::id::graphics_device);
			}

			render ();

		}

		void system_component::push_item (imaterial * material, imesh * mesh, const mat4 & transform) {
			render_item & item = _render_list.reserve_item ();

			item.material = material;
			item.mesh = mesh;
			item.transform = transform;

			render_item::set_render_bucket (item, _camera);
		}

	}
}