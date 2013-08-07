#ifndef	_ballistic_graphics_opengl_debug_h_
#define _ballistic_graphics_opengl_debug_h_

#include <ballistic.base.h>
#include <GL/glew.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

#		define gl_shader_source(x) \
			"#version 330 core\n" \
			#x;

#ifdef BALLISTIC_DEBUG

#	define gl_eval(x) \
		x; \
		{ \
			GLenum error = glGetError (); \
			if (error != GL_NO_ERROR) \
				debug_error ("GL Call [" << #x << "] Failed in file " << __FILE__ << " at line " << __LINE__ << " with " << ballistic::graphics::opengl_debug::error_to_string (error) ); \
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

#	define gl_eval_shader_compile(x)
#	define gl_eval_program_link(x)

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

			static string _vs_source;
			static string _fs_source;

			static GLint
				_debug_program_id,
				_vs_shader_id,
				_fs_shader_id,
				_color_uniform_id
				;

			static GLuint
				_vao_id,
				_vbo_id
				;

			static void load_shader ( const string & source, GLint id );

		public:

			// drawing tools 

			static void initialize ();

			static void draw_line ( const vec3 & p1, const vec3 & p2, const color & col );
			static void draw_rect ( const vec3 & p1, const vec3 & p2, const color & col );

		};

	}
}

#endif