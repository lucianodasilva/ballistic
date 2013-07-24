#ifndef	_ballistic_graphics_renderable_h_
#define _ballistic_graphics_renderable_h_

namespace ballistic {
	namespace graphics {

		class imesh;
		class imaterial;

		struct renderable {

			imesh *		mesh;
			imaterial * material;

		};

	}
}

#endif