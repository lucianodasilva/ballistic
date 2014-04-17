#include "ballistic.graphics.render_item.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

#include <limits>

namespace ballistic {
	namespace graphics {

		render_item::render_item ()	:
			mesh (nullptr),
			material (nullptr),
			bucket (std::numeric_limits < render_bucket >::max ())
		{}

		void render_item::set_render_bucket (render_item & item, camera * camera) {

			//// set layer
			//_b0 = (layer << 1);
			//// set translucent
			//if (!opaque) {
			//	_b0 ^= 0x01;
			//	_b1 = material;
			//	*((uint16_t *)&_b2) = depth;
			//} else {
			//	_b0 |= 0x01;
			//	*((uint16_t *)&_b1) = depth;
			//	_b3 = material;
			//}

			union {

				uint32_t uint_value;

				struct {
					uint8_t b0;
					uint8_t b1;
					uint8_t b2;
					uint8_t b3;
				};

			} byte_handler;

			try {
				if (item.material->opaque ()) {

					byte_handler.b0 = 0;
					byte_handler.b1 = item.material->run_id ();
					byte_handler.b2 = item.material->effect ()->run_id ();
					byte_handler.b3 = item.mesh->run_id ();

				} else {

					byte_handler.b0 = 1;

					uint16_t depth = camera->depth (item.transform);
					*((uint16_t *)&byte_handler.b1) = depth;

					byte_handler.b3 =
						item.material->effect ()->run_id ();

				}

				byte_handler.b0 += item.layer;

				item.bucket = byte_handler.uint_value;
			} catch (...) {
				debug_error ("render_item::set_render_bucket unable to properly calculate render bucket id.");
				item.bucket = 0;
			}

		}

	}
}