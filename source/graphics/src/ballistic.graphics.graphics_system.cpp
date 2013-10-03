#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.common_id.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		id_t graphics_system::get_id () {
			return ballistic::id::graphics::system;
		}

		graphics_system::graphics_system () :
			_device (nullptr),
			_camera (nullptr),
			_render_message (id::message_render)
		{}

		void graphics_system::set_device ( idevice * device ) {
			_device = device;
		}

		idevice * graphics_system::get_device () {
			return _device;
		}

		void graphics_system::set_camera (camera * cam) {
			_camera = cam;
		}

		const camera * graphics_system::get_camera () {
			return _camera;
		}

		void graphics_system::render () {

			if (!_device) {
				debug_error ("[ballistic::graphics::graphics_system::render] Graphics device not set!");
				return;
			}

			if (!get_game ()) {
				debug_error ("[ballistic::graphics::graphics_system::render] Graphics game not set!");
				return;
			}

			if (!_camera) {
				debug_error ("[ballistic::graphics::graphics_system::render] Active camera not set!");
				return;
			}

			_render_list.clear ();

			_device->set_view (_camera->get_view ());
			_device->set_proj (_camera->get_proj ());
			
			//_camera->make_perspective_proj(0.78539, 1.0, .0, 100.);
			
			mat4
				debug_proj = _camera->get_proj (),
				debug_view = _camera->get_view ();
			
			mat4 debug_t = debug_proj * debug_view;
			vec3 debug_pos (.5, .0, .0);
			
			debug_pos = debug_t * debug_pos;

			// notify entities with visuals
			get_game ()->send_message (_render_message);

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

		void graphics_system::notify ( ballistic::message & message ) {

			if (message.get_id () != ballistic::id::message_update) return;

			render ();

		}

		void graphics_system::push_item (imaterial * material, imesh * mesh, const mat4 & transform) {
			render_item & item = _render_list.reserve_item ();

			item.material = material;
			item.mesh = mesh;
			item.transform = transform;

			render_item::set_render_bucket (item, _camera);
		}

	}
}