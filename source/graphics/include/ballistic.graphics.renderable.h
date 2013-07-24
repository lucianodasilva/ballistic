#ifndef	_ballistic_graphics_renderable_h_
#define _ballistic_graphics_renderable_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class imesh;
		class imaterial;

		struct renderable {

			imesh *		mesh;
			imaterial * material;
			mat4 &		transform;

		};

	}
}

#endif