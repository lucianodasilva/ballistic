#include "ballistic.graphics.opengl_mesh.h"

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		opengl_mesh::opengl_mesh () : _vertex_buffer_id(0) {}
		
		opengl_mesh::~opengl_mesh() {
			if (_vertex_buffer_id > 0) {
				glDeleteBuffers (1, &_vertex_buffer_id);
				glDeleteBuffers (1, &_index_buffer_id);
			}
		}
		
		void opengl_mesh::set_data (
			vertex vert_buffer [],
			uint16 index_buffer []
		){
			
			glGenBuffers (1, &_vertex_buffer_id);
			glGenBuffers (1, &_index_buffer_id);
			
			// Interleaved vertex buffer
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
			glBufferData (GL_ARRAY_BUFFER, sizeof (vert_buffer), (GLvoid *)&vert_buffer[0], GL_STATIC_DRAW);
			
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (index_buffer), (GLvoid *)&index_buffer[0], GL_STATIC_DRAW);

			_vertex_buffer_size = sizeof (vert_buffer) / sizeof (vertex);
		}
		
		void opengl_mesh::attach () {
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glVertexPointer (3, GL_FLOAT, sizeof (vertex), 0);
			glTexCoordPointer (2, GL_FLOAT, sizeof (vertex), (GLvoid *)sizeof (vec3));
			
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
		}
		
		void opengl_mesh::render () {
			glDrawElements (GL_TRIANGLES, _vertex_buffer_size, GL_UNSIGNED_SHORT, 0);
		}
		
		void opengl_mesh::detach() {
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glBindBuffer (GL_VERTEX_ARRAY, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}