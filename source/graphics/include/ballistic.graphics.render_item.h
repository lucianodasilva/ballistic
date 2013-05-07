#ifndef	_ballistic_graphics_render_item_h_
#define _ballistic_graphics_render_item_h_

#include "ballistic.graphics.irenderable.h"
#include "ballistic.graphics.material.h"

#include <glm.hpp>

using namespace glm;

namespace ballistic {
	namespace graphics {

		struct render_item {
			
			irenderable * render_object;
			mat4 transform;
			material * material;

			inline render_item () : render_object (nullptr), material (nullptr) {}

			inline render_item ( irenderable * renderable, const mat4 & transf_matrix, graphics::material * mat )
				: render_object (renderable), transform (transf_matrix), material (mat) {}

		};

	}
}

#endif