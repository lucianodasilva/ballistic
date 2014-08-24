#ifndef	_ballistic_graphics_object_h_
#define _ballistic_graphics_object_h_

#include <ballistic.base.h>

#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class imesh;
		class material;

		typedef uint32_t render_bucket;

		struct render_item {

			imesh *			mesh;
			material *		material;
			mat4			transform;

			uint8_t			layer;

			render_bucket	bucket;

			render_item ();

			static void set_render_bucket (render_item & item, camera * camera);

		};


	}
}

#endif