#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		opengl_effect::opengl_effect () : _shader_program_id(-1) {}

		opengl_effect::~opengl_effect () {
			if (_shader_program_id != -1)
				glDeleteProgram (_shader_program_id);
		}
		
		bool opengl_effect::is_shader_ok(GLint shader_id) {
			GLint compiler_state;
			glGetShaderiv (shader_id, GL_COMPILE_STATUS, &compiler_state);
			
			return compiler_state == GL_TRUE;
		}
		
		bool opengl_effect::is_link_ok(GLint program_id) {
			GLint linker_state;
			glGetProgramiv (program_id, GL_LINK_STATUS, &linker_state);
			
			return linker_state == GL_TRUE;
		}
		
		void opengl_effect::load_gl_shader (GLint shader_id, const string & source) {
			const char * source_ptr = source.c_str ();
			int32 source_length = source.length ();
			
			glShaderSource (shader_id, 1, (const GLchar **)&source_ptr, &source_length);
			glCompileShader (shader_id);
			
			gl_eval_shader_compile (shader_id);
		}
		
		void opengl_effect::load (
			const string & vs_shader_source,
			const string & fs_shader_source
		){
			gl_eval_scope(opengl_effect::load);
			
			_shader_program_id = glCreateProgram ();
			
			GLint
				_vs_shader_id = glCreateShader (GL_VERTEX_SHADER),
				_fs_shader_id = glCreateShader (GL_FRAGMENT_SHADER);
			
			load_gl_shader (_vs_shader_id, vs_shader_source);
			load_gl_shader (_fs_shader_id, fs_shader_source);
			
			if (!(is_shader_ok(_vs_shader_id) && is_shader_ok(_fs_shader_id))) {
				debug_warn("GL Shader compilation failed. Shader program not loaded.");
				glDeleteProgram (_shader_program_id);
				_shader_program_id = -1;
				
				return;
			}
			
			glAttachShader (_shader_program_id, _vs_shader_id);
			glAttachShader (_shader_program_id, _fs_shader_id);
			
			glLinkProgram (_shader_program_id);
			
			glDeleteShader (_vs_shader_id);
			glDeleteShader (_fs_shader_id);
			
			if (!is_link_ok(_shader_program_id)) {
				debug_warn ("GL Shader linking failed. Shader program not loaded");
				glDeleteProgram (_shader_program_id);
				
				_shader_program_id = -1;
			}
			
			// Discover uniforms
			int total = -1;
			glGetProgramiv( _shader_program_id, GL_ACTIVE_UNIFORMS, &total );
			for(int i=0; i<total; ++i)  {
				int name_len=-1, num=-1;
				GLenum type = GL_ZERO;
				char name[100];
				glGetActiveUniform( _shader_program_id, GLuint(i), sizeof(name)-1,
								   &name_len, &num, &type, name );
				
				if (type == GL_FLOAT_VEC4) {
					debug_print ("bingo");
				}
				
				name[name_len] = 0;
				GLuint location = glGetUniformLocation( _shader_program_id, name );
			}
			
		}
		
		void opengl_effect::apply () {
			
			if (_shader_program_id == -1) {
				glUseProgram (0);
				return;
			}
			
			glUseProgram (_shader_program_id);
		}

	}
}