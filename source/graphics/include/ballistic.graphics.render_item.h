#ifndef	_ballistic_graphics_object_h_
#define _ballistic_graphics_object_h_

#include <ballistic.base.h>

#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class imesh;
		class imaterial;

		typedef uint32 render_bucket;

		struct render_item {

			imesh *			mesh;
			imaterial *		material;
			mat4			transform;

			render_bucket	bucket;

			static void set_render_bucket (render_item & item, camera * camera);

		};


	}
}

#endif