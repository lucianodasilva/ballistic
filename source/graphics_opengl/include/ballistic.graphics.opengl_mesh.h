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

			uint8_t _run_id;
			
			GLuint
				_vertex_array_id,
				_vertex_buffer_id,
				_index_buffer_id,
				_index_buffer_size;

			aabox _bounding_box;
			
			static GLint calc_stride (mesh_attribute attributes);
			
			static uint32_t set_attributes (mesh_attribute attributes);
			static GLint add_attribute (GLint id, GLint size, GLenum type, GLint stride, GLint offset);

			static aabox calc_aabox (uint8_t * data_buffer, int32_t data_buffer_size, uint32_t offset);

		public:
			
			opengl_mesh ( const id_t & id, uint8_t run_id );
			~opengl_mesh ();

			virtual uint8_t run_id ();
			
			virtual void set_data (
				uint8_t *			data_buffer,
				int32_t			data_buffer_size,
				uint16_t *		index_buffer,
				uint32_t			index_buffer_size,
				mesh_attribute	attributes,
				bool			dynamic = false
			);

			virtual void update_data (
				uint8_t *			data_buffer,
				int32_t			data_buffer_size,
				mesh_attribute	attributes
			);

			virtual void update_index (
				uint16_t *		index_buffer,
				uint32_t			index_buffer_size
			);
			
			virtual void apply (idevice * device);
			virtual void render ();

			virtual aabox bounding_box () const;
			
		};
		
	}
}


#endif