#ifndef	_ballistic_graphics_opengl_effect_h_
#define _ballistic_graphics_opengl_effect_h_

#include <ballistic.graphics.h>
#include <gl/glew.h>

namespace ballistic {
	namespace graphics {

		class opengl_effect : public ballistic::graphics::ieffect {
		private:
			
			GLint _shader_program_id;
			
			bool is_shader_ok (GLint shader_id);
			bool is_link_ok (GLint program_id);
			
			void load_gl_shader (GLint shader_id, const string & source);

		public:
			
			opengl_effect ();
			~opengl_effect ();
			
			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			);
			
			virtual void apply ();

		};

	}
}

#endif