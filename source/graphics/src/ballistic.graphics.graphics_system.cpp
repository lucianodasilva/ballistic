#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.common_id.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		id_t graphics_system::id () {
			return ballistic::id::graphics::system;
		}

		graphics_system::graphics_system () :
			_device (nullptr),
			_camera (nullptr),
			_render_message (id::message_render)
		{}

		void graphics_system::device ( idevice * dev ) {
			_device = dev;
		}

		idevice * graphics_system::device () {
			return _device;
		}

		void graphics_system::camera (ballistic::graphics::camera * cam) {
			_camera = cam;
		}

		const ballistic::graphics::camera * graphics_system::camera () {
			return _camera;
		}

		void graphics_system::render () {
			
			mat4
				current_view,
				normal_matrix;

			if (!_device) {
				debug_error ("graphics device not set! will not render");
				return;
			}

			if (!_camera) {
				debug_error ("active camera not set! will not render");
				return;
			}
			
			current_view = _camera->view ();

			_device->view (current_view);
			_device->proj (_camera->proj ());

			// notify entities with visuals
			game::instance.global_notifier.notify(_render_message);

			// sort
			_render_list.sort ();

			_device->alpha_blend (false);
			_device->clear ();
			_device->begin_frame ();

			// render loop ---------------------------
			uint32_t render_count = _render_list.size ();
			imaterial * material = nullptr;
			ieffect * effect = nullptr;
			imesh * mesh = nullptr;
			itexture * texture = nullptr;

			bool alpha_blend = false;

			for (uint32_t i = 0; i < render_count; ++i) {
				render_item & item = _render_list [i];

				if (item.material->effect () != effect) {
					effect = item.material->effect ();
					_device->activate (effect);
				}

				if (item.material != material) {
					material = item.material;
					_device->activate (material);
				}

				if (item.material->texture () != texture) {
					texture = item.material->texture ();
					_device->activate (texture);
				}

				if (item.material->opaque () != alpha_blend) {
					alpha_blend = true;
					_device->alpha_blend (true);
				}

				if (item.mesh != mesh) {
					mesh = item.mesh;
					_device->activate (mesh);
				}

				// update model matrices
				mat4 mv = current_view * item.transform;
				normal_matrix = mv.transpose ().invert ();
				
				_device->normal (normal_matrix);
				_device->model (item.transform);
				
				// render the stuffs
				_device->draw_active_mesh ();

			}

			_device->end_frame ();
			_device->present ();

			_render_list.clear ();
		}

		void graphics_system::notify ( entity * sender, ballistic::message & message ) {
			render ();
		}

		void graphics_system::attach () {
			game::instance.global_notifier.attach (id::message_update, this);
		}

		void graphics_system::detach () {
			game::instance.global_notifier.detach (id::message_update, this);
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