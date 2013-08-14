#ifndef _ballistic_graphics__ballistic_graphics_opengl_mesh_h_
#define _ballistic_graphics__ballistic_graphics_opengl_mesh_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		class opengl_mesh : public ballistic::graphics::imesh
		{
		private:

			uint8 _run_id;
			
			GLuint
				_vertex_array_id,
				_vertex_buffer_id,
				_index_buffer_id,
				_index_buffer_size;
			
			static GLint calc_stride (mesh_attribute attributes);
			
			static void  set_attributes (mesh_attribute attributes);
			static GLint add_attribute (GLint id, GLint size, GLenum type, GLint stride, GLint offset);

		public:
			
			opengl_mesh ( uint8 run_id );
			~opengl_mesh ();

			virtual uint8 get_run_id ();
			
			virtual void set_data (
				uint8 *			data_buffer,
				int32			data_buffer_size,
				uint16 *		index_buffer,
				uint32			index_buffer_size,
				mesh_attribute	attributes,
				bool			dynamic = false
			);

			virtual void update_data (
				uint8 *			data_buffer,
				int32			data_buffer_size,
				mesh_attribute	attributes
			);

			virtual void update_index (
				uint16 *		index_buffer,
				uint32			index_buffer_size
			);
			
			virtual void apply ();
			virtual void render ();
			
		};
		
	}
}


#endif