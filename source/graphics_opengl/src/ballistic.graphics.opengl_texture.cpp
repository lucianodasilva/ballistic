#include "ballistic.graphics.opengl_texture.h"
#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		GLint opengl_texture::convert_filter_to_gl (const texture_filter & v) {
			if ( v == texture_filter_linear_mipmap_linear)
				return GL_LINEAR_MIPMAP_LINEAR;
			else if ( v == texture_filter_linear_mipmap_nearest)
				return GL_LINEAR_MIPMAP_NEAREST;
			else if ( v == texture_filter_nearest )
				return GL_NEAREST;
			else
				return GL_LINEAR;
		}

		GLint opengl_texture::convert_wrap_to_gl (const texture_wrap & v) {
			if (v == texture_wrap_clamp_to_border)
				return GL_CLAMP_TO_BORDER;
			else if (v == texture_wrap_clamp_to_edge)
				return GL_CLAMP_TO_EDGE;
			else if (v == texture_wrap_mirrored_repeat)
				return GL_MIRRORED_REPEAT;
			else
				return GL_REPEAT;
		}

		GLint opengl_texture::convert_format_to_gl (const texture_format & v) {
			if (v == texture_format_rgb)
				return GL_RGB;
			else
				return GL_RGBA;
		}

		opengl_texture::opengl_texture (const id_t & id, uint8_t run_id)
			: itexture (id), _run_id (run_id), _texture_id (0)
		{}

		opengl_texture::~opengl_texture () {
			if (_texture_id)
				glDeleteTextures (1, &_texture_id);
		}

		uint8_t opengl_texture::run_id () { return _run_id; }

		void opengl_texture::set_data (
			char * data,
			uint32_t width,
			uint32_t height,
			const texture_format & format,
			const texture_wrap & wrap_s_v,
			const texture_wrap & wrap_t_v,
			const texture_filter & mag_filter_v,
			const texture_filter & min_filter_v
		) {
			gl_eval_scope (create texture);

			glGenTextures (1, &_texture_id);
			
			// activate texture
			glBindTexture (GL_TEXTURE_2D, _texture_id);
		 
			glTexImage2D (
				GL_TEXTURE_2D,
				0,
				convert_format_to_gl (format),
				width,
				height,
				0,
				convert_format_to_gl (format),
				GL_UNSIGNED_BYTE,
				data
			);

			//glEnable (GL_TEXTURE_2D);
			glGenerateMipmap (GL_TEXTURE_2D);

			_min_filter = convert_filter_to_gl (min_filter_v);
			_mag_filter = convert_filter_to_gl (mag_filter_v);
			
			_wrap_s = convert_wrap_to_gl (wrap_s_v);
			_wrap_t = convert_wrap_to_gl (wrap_t_v);
		 
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _mag_filter);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _min_filter);

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap_s);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap_t);

			// offset for better quality
			glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.0F);
		}

		//void opengl_texture::update_data (
		//	char * data,
		//	int width,
		//	int height,
		//	const texture_wrap & wrap_s_v,
		//	const texture_wrap & wrap_t_v,
		//	const texture_filter & mag_filter_v,
		//	const texture_filter & min_filter_v
		//) {
		//
		//}

		void opengl_texture::apply (idevice * device) {
			glActiveTexture (GL_TEXTURE0);
			glBindTexture (GL_TEXTURE_2D, _texture_id);
		}

	}
}