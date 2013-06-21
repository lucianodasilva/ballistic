#ifndef _ballistic_graphics__ballistic_graphics_dx_mesh_h_
#define _ballistic_graphics__ballistic_graphics_dx_mesh_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

namespace ballistic {
	namespace graphics {
		
		class dx_mesh : public ballistic::graphics::imesh
		{
		private:
			
			uint32
				_vertex_buffer_id,
				_vertex_buffer_size,
				_index_buffer_id,
				_index_buffer_size;
			
			
		public:
			
			dx_mesh ();
			~dx_mesh ();
			
			virtual void set_data (
				vertex vert_buffer [],
				uint32 vert_buffer_size,
				uint16 index_buffer [],
				uint32 index_buffer_size
			);
			
			virtual void attach ();
			virtual void render ();
			virtual void detach ();
			
		};
		
	}
}


#endif