#ifndef _ballistic_graphics_imesh_h_
#define	_ballistic_graphics_imesh_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		
		struct vertex {
			vec3 position;
			vec2 uv;
		};

		class imesh {
		public:
			
			virtual void set_data (
								   vertex vert_buffer [],
								   uint16 index_buffer []
								   ) = 0;

			virtual void attach () = 0;
			virtual void render () = 0;
			virtual void detach () = 0;
		};

	}
}

#endif