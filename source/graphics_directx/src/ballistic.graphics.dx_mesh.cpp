#include "ballistic.graphics.dx_mesh.h"

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		dx_mesh::dx_mesh () : _vertex_buffer_id(0) {}
		
		dx_mesh::~dx_mesh() {
			if (_vertex_buffer_id > 0) {
				glDeleteBuffers (1, &_vertex_buffer_id);
				glDeleteBuffers (1, &_index_buffer_id);
			}
		}
		
		void dx_mesh::set_data (
			vertex vert_buffer [],
			uint32 vert_buffer_size,
			uint16 index_buffer [],
			uint32 index_buffer_size
		){
			
			_vertex_buffer_size = vert_buffer_size;
			_index_buffer_size = index_buffer_size;
			
			glGenBuffers (1, &_vertex_buffer_id);
			glGenBuffers (1, &_index_buffer_id);
			
			// Interleaved vertex buffer
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertex) * _vertex_buffer_size, (GLvoid *)&vert_buffer[0], GL_STATIC_DRAW);
			
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (uint16) * _index_buffer_size, (GLvoid *)&index_buffer[0], GL_STATIC_DRAW);
		}
		
		void dx_mesh::attach () {
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glVertexPointer (3, GL_FLOAT, sizeof (vertex), 0);
			glTexCoordPointer (2, GL_FLOAT, sizeof (vertex), (GLvoid *)sizeof (vec3));
			
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
		}
		
		void dx_mesh::render () {
			glDrawElements (GL_TRIANGLES, _vertex_buffer_size, GL_UNSIGNED_SHORT, 0);
		}
		
		void dx_mesh::detach() {
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glBindBuffer (GL_VERTEX_ARRAY, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}