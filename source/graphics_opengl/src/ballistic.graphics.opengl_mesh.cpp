#include "ballistic.graphics.opengl_mesh.h"

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		opengl_mesh::opengl_mesh () {
			
		}
		
		void opengl_mesh::set_data (
			vertex * vert_buffer,
			uint32 vert_buffer_size,
			uint16 * index_buffer,
			uint32 index_buffer_size
		){
			
			glGenBuffers (1, &_vertex_buffer_id);
			glGenBuffers (1, &_index_buffer_id);
			
			
		}
		
	}
}