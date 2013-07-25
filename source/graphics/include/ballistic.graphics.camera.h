#ifndef _ballistic_graphics_camera_h_
#define _ballistic_graphics_camera_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class camera {
		private:

			real _near;
			real _far;

			real _depth_divisor;

		public:

			vec3 target;
			vec3 position;
			vec3 up;

			// constructors
			camera ();
			camera (const camera & v);
			camera (real near, real far);

			// attribution
			const camera & operator = (const camera &v);

			// methods
			uint16 get_depth (mat4 & transform);

			mat4 get_view ();
		};

	}
}

#endif