#ifndef _ballistic_graphics__ballistic_graphics_opengl_mesh_h_
#define _ballistic_graphics__ballistic_graphics_opengl_mesh_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

namespace ballistic {
	namespace graphics {
		
		class opengl_mesh : public ballistic::graphics::imesh
		{
		private:
			
			uint32
				_vertex_buffer_id,
				_vertex_buffer_size,
				_index_buffer_id;
			
			
		public:
			
			opengl_mesh ();
			~opengl_mesh ();
			
			virtual void set_data (
				vertex vert_buffer [],
				uint16 index_buffer []
			);
			
			virtual void attach ();
			virtual void render ();
			virtual void detach ();
			
		};
		
	}
}


#endif