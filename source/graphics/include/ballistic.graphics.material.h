#ifndef	_ballistic_graphics_material_h_
#define _ballistic_graphics_material_h_

#include <glm.hpp>

using namespace glm;

namespace ballistic {
	namespace graphics {

		class material {
		public:

			vec4 color;

			void activate ();
			void deactivate ();
		};

	}
}

#endif