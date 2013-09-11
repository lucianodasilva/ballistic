#include "ballistic.graphics.render_item.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		void render_item::set_render_bucket (render_item & item, const camera & camera) {

			//// set layer
			//_b0 = (layer << 1);
			//// set translucent
			//if (!opaque) {
			//	_b0 ^= 0x01;
			//	_b1 = material;
			//	*((uint16 *)&_b2) = depth;
			//} else {
			//	_b0 |= 0x01;
			//	*((uint16 *)&_b1) = depth;
			//	_b3 = material;
			//}

			union {

				uint32 uint_value;

				struct {
					uint8 b0;
					uint8 b1;
					uint8 b2;
					uint8 b3;
				};

			} byte_handler;

			try {
				if (item.material->get_opaque ()) {

					byte_handler.b0 = 0;
					byte_handler.b1 = item.material->get_run_id ();
					byte_handler.b2 = item.material->get_effect ()->get_run_id ();
					byte_handler.b3 = item.mesh->get_run_id ();

				} else {

					byte_handler.b0 = 1;

					uint16 depth = camera.get_depth (item.transform);
					*((uint16 *)&byte_handler.b1) = depth;

					byte_handler.b3 =
						item.material->get_effect ()->get_run_id ();

				}

				item.bucket = byte_handler.uint_value;
			} catch (...) {
				debug_error ("render_item::set_render_bucket unable to properly calculate render bucket id.");
				item.bucket = 0;
			}

		}

	}
}