#ifndef _ballistic_graphics__ballistic_graphics_opengl_texture_h_
#define _ballistic_graphics__ballistic_graphics_opengl_texture_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		class opengl_texture : public ballistic::graphics::itexture
		{
		private:

			uint8_t _run_id;

			GLint
				_format;

			GLint
				_wrap_s,
				_wrap_t;

			GLint
				_mag_filter,
				_min_filter;

			GLuint _texture_id;

			GLint convert_wrap_to_gl (const texture_wrap & v);
			GLint convert_filter_to_gl (const texture_filter & v);
			GLint convert_format_to_gl (const texture_format & v);

		public:

			opengl_texture (const id_t & id, uint8_t run_id);
			virtual ~opengl_texture ();

			// properties
			virtual uint8_t run_id ();

			// load data
			virtual void set_data (
				char * data, 
				uint32_t width, 
				uint32_t height,
				const texture_format & format,
				const texture_wrap & wrap_s_v = texture_wrap_clamp_to_border,
				const texture_wrap & wrap_t_v = texture_wrap_clamp_to_border,
				const texture_filter & mag_filter_v = texture_filter_nearest,
				const texture_filter & min_filter_v = texture_filter_nearest
			);

			virtual void update_data (
				char * data,
				uint32_t x,
				uint32_t y,
				uint32_t width,
				uint32_t height
			);

			virtual void apply (idevice * device);
			
		};
		
	}
}


#endif