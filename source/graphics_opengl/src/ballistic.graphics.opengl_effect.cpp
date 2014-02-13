#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		opengl_effect::opengl_effect (uint8_t run_id) : _shader_program_id(-1), _run_id (run_id) {}

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
			int32_t source_length = source.length ();
			
			glShaderSource (shader_id, 1, (const GLchar **)&source_ptr, &source_length);
			glCompileShader (shader_id);
			
			gl_eval_shader_compile (shader_id);
		}

		uint8_t opengl_effect::get_run_id () { return _run_id; }

		opengl_constant opengl_effect::get_constant (id_t id) const {
			auto it = _constants.find (id);

			if (it != _constants.end ())
				return it->second;

			//debug_error ("[ballistic::graphics::opengl_effect::get_constant] GL Effect get constant with id:" << id << " not found.");
			return opengl_constant ();
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
				debug_warn("[ballistic::graphics::opengl_effect::load] GL Shader compilation failed. Shader program not loaded.");
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
				debug_warn ("[ballistic::graphics::opengl_effect::load] GL Shader linking failed. Shader program not loaded");
				glDeleteProgram (_shader_program_id);
				
				_shader_program_id = -1;
			}
			
			// Discover uniforms
			int total = -1;
			glGetProgramiv (_shader_program_id, GL_ACTIVE_UNIFORMS, &total);
			for (int i = 0; i < total; ++i) {
				int name_len = -1, num = -1;
				GLenum type = GL_ZERO;
				char name [100];
				glGetActiveUniform (_shader_program_id, GLuint (i), sizeof(name)-1,
									&name_len, &num, &type, name);

				name [name_len] = 0;
				GLuint location = glGetUniformLocation (_shader_program_id, name);

				id_t id = string_to_id (name);

				_constants [id] = opengl_constant (location, id);
			}
		}
		
		void opengl_effect::apply (idevice * device) {
			
			if (_shader_program_id == -1) {
				glUseProgram (0);
				return;
			}
			
			glUseProgram (_shader_program_id);
		}

		void opengl_effect::set_constant (opengl_constant & u, int32_t v) {
			if (!u.is_defined ()) {
				//debug_error ("GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (int32_t));
			glUniform1i (u.location, v);
		}

		void opengl_effect::set_constant (opengl_constant & u, real v) {
			if (!u.is_defined ()) {
				//debug_error ("[ballistic::graphics::opengl_effect::set_constant] GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (real));
			glUniform1f (u.location, v);
		}

		void opengl_effect::set_constant (opengl_constant & u, const vec2 & v) {
			if (!u.is_defined ()) {
				//debug_error ("[ballistic::graphics::opengl_effect::set_constant] GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (vec2));
			glUniform2f (u.location, v.x, v.y);
		}

		void opengl_effect::set_constant (opengl_constant & u, const vec3 & v) {
			if (!u.is_defined ()) {
				//debug_error ("[ballistic::graphics::opengl_effect::set_constant] GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (vec3));
			glUniform3f (u.location, v.x, v.y, v.z);
		}

		void opengl_effect::set_constant (opengl_constant & u, const vec4 & v) {
			if (!u.is_defined ()) {
				//debug_error ("[ballistic::graphics::opengl_effect::set_constant] GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (vec4));
			glUniform4f (u.location, v.x, v.y, v.z, v.w);
		}

		void opengl_effect::set_constant (opengl_constant & u, const mat4 & v) {
			if (!u.is_defined ()) {
				//debug_error ("[ballistic::graphics::opengl_effect::set_constant] GL constant " << u.id << " location not defined");
				return;
			}

			gl_eval_scope (opengl_effect::set_constant (mat4));
			glUniformMatrix4fv (u.location, 1, false, (GLfloat *)&v);
		}

	}
}