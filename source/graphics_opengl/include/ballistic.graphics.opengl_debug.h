#ifndef	_ballistic_graphics_opengl_debug_h_
#define _ballistic_graphics_opengl_debug_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <GL/glew.h>
#include <string>

#include "ballistic.graphics.opengl_effect.h"

using namespace std;

namespace ballistic {
	namespace graphics {

#		define gl_shader_source(x) \
			"#version 330 core\n" \
			#x

#ifdef BALLISTIC_DEBUG

#	define gl_eval(x) \
		x; \
		{ \
			GLenum error = glGetError (); \
			if (error != GL_NO_ERROR) \
				debug_error ("gl call [" << #x << "] failed with " << ballistic::graphics::opengl_debug::error_to_string (error) ); \
		}

#	define gl_eval_shader_compile(shader_id) \
		ballistic::graphics::opengl_debug::eval_shader_compile (shader_id)

#	define gl_eval_program_link(program_id) \
		ballistic::graphics::opengl_debug::eval_program_link (program_id);

#	define gl_eval_scope(scope_name) \
	ballistic::graphics::opengl_debug::eval_scope __gl_evaluate_scope__ = {#scope_name}


#else

#	define gl_eval(x) \
	x

#	define gl_eval_shader_compile(x) {}
#	define gl_eval_program_link(x) {}
#	define gl_eval_scope(x) {}

#endif

		class opengl_debug {
		public:

			// generic tools
			static string error_to_string ( GLenum error );

			static void eval_shader_compile (GLint shader_id);

			static void eval_program_link (GLint program_id);

			struct eval_scope {
				string method_name;
				~eval_scope ();
			};

		private:
			
			static ballistic::graphics::opengl_effect	_effect;
			static ballistic::graphics::opengl_constant _color_uniform;

			static string _vs_source;
			static string _fs_source;

			static GLuint
				_vao_id,
				_vbo_id
				;

		public:

			// drawing tools 

			static void initialize ();

			static void draw_line ( const vec3 & p1, const vec3 & p2, const color & col );
			static void draw_rect ( const vec3 & p1, const vec3 & p2, const color & col );

			static void draw_text (const vec3 & pos, const color & col, const char text []);

		};

	}
}

#endif