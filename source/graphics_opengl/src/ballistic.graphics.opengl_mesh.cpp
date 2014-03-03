#include "ballistic.graphics.opengl_mesh.h"

#include <GL/glew.h>

#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		GLint opengl_mesh::calc_stride (mesh_attribute attributes) {
			GLint stride = 0;

			if (attributes & mesh_attribute_position)
				stride += sizeof (vec3);
			if (attributes & mesh_attribute_uv)
				stride += sizeof (vec2);
			if (attributes & mesh_attribute_normal)
				stride += sizeof (vec3);

			return stride;
		}

		void opengl_mesh::set_attributes (mesh_attribute attributes) {
			GLint attribute_id = 0;
			GLint attribute_offset = 0;
			GLint attribute_stride = calc_stride (attributes);

			if (attributes & mesh_attribute_position) {
				gl_eval_scope ([ballistic::graphics::opengl_mesh::set_attributes] mesh_attribute_position);
				attribute_offset = add_attribute (
					1,
					3,
					GL_FLOAT,
					attribute_stride,
					attribute_offset
					);
			}

			if (attributes & mesh_attribute_uv) {
				gl_eval_scope ([ballistic::graphics::opengl_mesh::set_attributes] mesh_attribute_uv);
				attribute_offset = add_attribute (
					2,
					2,
					GL_FLOAT,
					attribute_stride,
					attribute_offset
					);
			}

			if (attributes & mesh_attribute_normal) {
				gl_eval_scope ([ballistic::graphics::opengl_mesh::set_attributes] mesh_attribute_normal);
				attribute_offset = add_attribute (
					3,
					3,
					GL_FLOAT,
					attribute_stride,
					attribute_offset
					);
			}
		}

		GLint opengl_mesh::add_attribute (GLint id, GLint size, GLenum type, GLint stride, GLint offset) {
			glVertexAttribPointer (
				id,
				size,         // number of elements
				type,         // type
				GL_FALSE,     // normalized?
				stride,
				(GLvoid*)offset // array buffer offset in bytes
				);

			glEnableVertexAttribArray (id);
	
			return offset + size * sizeof (GL_FLOAT);
		}
		
		opengl_mesh::opengl_mesh ( id_t id, uint8_t run_id ) :
			iresource (id),
			imesh (*this),
			_run_id (run_id), 
			_vertex_array_id (0),
			_vertex_buffer_id(0),
			_index_buffer_id (0)
		{}
		
		opengl_mesh::~opengl_mesh() {
			if (_vertex_buffer_id > 0) {
				glDeleteBuffers (1, &_vertex_buffer_id);
				glDeleteBuffers (1, &_index_buffer_id);
			}
		}
		
		uint8_t opengl_mesh::run_id () { return _run_id; }

		void opengl_mesh::set_data (
			uint8_t *			data_buffer,
			int32_t			data_buffer_size,
			uint16_t *		index_buffer,
			uint32_t			index_buffer_size,
			mesh_attribute	attributes,
			bool			dynamic
		){
			_index_buffer_size = index_buffer_size;

			gl_eval_scope (opengl_mesh::set_data);

			// Create vertex buffer
			glGenBuffers (1, &_vertex_buffer_id);
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);

			// Set vertex buffer data
			glBufferData (GL_ARRAY_BUFFER, data_buffer_size, (GLvoid *)data_buffer, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

			// Create index buffer
			glGenBuffers (1, &_index_buffer_id);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
			
			// Set index buffer data
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_size, (GLvoid *)index_buffer, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

			// Unbind buffers
			glBindBuffer (GL_ARRAY_BUFFER, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

			// Create Vertex Array Object
			glGenVertexArrays (1, &_vertex_array_id);
			glBindVertexArray (_vertex_array_id);

			// Setup vertex array object
			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);

			set_attributes (attributes);

			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);

			// Reset state machine
			glBindVertexArray (0);
			glBindBuffer (GL_ARRAY_BUFFER, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void opengl_mesh::update_data (
			uint8_t *			data_buffer,
			int32_t			data_buffer_size,
			mesh_attribute	attributes
		){
			if (_vertex_array_id == 0) {
				debug_error ("gL cannot update data from undefined mesh");
				return;
			}

			gl_eval_scope (opengl_mesh::update_data);

			glBindVertexArray (_vertex_array_id);
			glBufferData (
				GL_ARRAY_BUFFER,
				data_buffer_size,
				(GLvoid *)data_buffer,
				GL_DYNAMIC_DRAW);

			set_attributes (attributes);

			// Reset state machine
			glBindVertexArray (0);
			glBindBuffer (GL_ARRAY_BUFFER, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void opengl_mesh::update_index (
			uint16_t *		index_buffer,
			uint32_t			index_buffer_size
		){
			if (_vertex_array_id == 0) {
				debug_error ("gl cannot update data from undefined mesh");
				return;
			}

			gl_eval_scope (opengl_mesh::update_index);

			_index_buffer_size = index_buffer_size;
			glBindVertexArray (_vertex_array_id);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_size, (GLvoid *)index_buffer,GL_DYNAMIC_DRAW);

			// Reset state machine
			glBindVertexArray (0);
			glBindBuffer (GL_ARRAY_BUFFER, 0);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		
		void opengl_mesh::apply (idevice * device) {
			gl_eval_scope (ballistic::graphics::opengl_mesh::apply);
			glBindVertexArray (_vertex_array_id);
		}
		
		void opengl_mesh::render () {
			gl_eval_scope (ballistic::graphics::opengl_mesh::render);
			glDrawElements (GL_TRIANGLES, _index_buffer_size / sizeof (uint16_t), GL_UNSIGNED_SHORT, 0);
		}

	}
}