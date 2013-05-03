#ifndef	_ballistic_graphics_render_item_h_
#define _ballistic_graphics_render_item_h_

#include "ballistic.graphics.irenderable.h"

#include <glm.hpp>

using namespace glm;

namespace ballistic {
	namespace graphics {

		struct render_item {
			
			irenderable * render_object;
			mat4 transform;

			inline render_item () : render_object (nullptr) {}

			inline render_item ( irenderable * renderable, const mat4 & transf_matrix )
				: render_object (renderable), transform (transf_matrix) {}

		};

	}
}

#endif