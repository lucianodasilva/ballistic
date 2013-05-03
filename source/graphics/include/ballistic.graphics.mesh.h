#ifndef	_ballistic_graphics_mesh_h_
#define _ballistic_graphics_mesh_h_

#include "ballistic.graphics.irenderable.h"

#include <glm.hpp>
#include <Ballistic.h>

using namespace glm;

namespace ballistic {
	namespace graphics {

		class mesh : public irenderable {
		public:

			struct vertex {
				vec3 position;
				vec2 uv;
			};

		private:

			uint32 _v_buffer_id;
			uint32 _i_buffer_id;
			uint32 _face_count;

		public:

			mesh ();
			mesh ( vertex v_buffer [], uint16 index_buffer [] );
			virtual ~mesh ();

			void set_data ( vertex v_buffer [], uint16 index_buffer [] );
			void clear_data ();

			virtual void render ();

		};

	}
}

#endif