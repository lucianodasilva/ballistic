#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		opengl_effect::opengl_effect (const id_t & id, uint8_t run_id) :
			ieffect (id),
			_shader_program_id(-1),
			_run_id (run_id)
		{}

		opengl_effect::~opengl_effect () {
			if (_shader_program_id != -1)
				glDeleteProgram (_shader_program_id);

			// clean up constants
			for (auto it : _constants)
				delete it.second;
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

		//iconstant * opengl_effect::create_constant (GLuint location, const id_t & id, GLuint type) {
		//	switch (type) {
		//	case (GL_UNSIGNED_INT):
		//		return new opengl_constant < uint32_t > (location, id);
		//		break;
		//	case (GL_INT):
		//		return new opengl_constant < int32_t > (location, id);
		//		break;
		//	case (GL_FLOAT):
		//		return new opengl_constant < real > (location, id);
		//		break;
		//	case (GL_FLOAT_VEC2):
		//		return new opengl_constant < vec2 > (location, id);
		//		break;
		//	case (GL_FLOAT_VEC3):
		//		return new opengl_constant < vec3 > (location, id);
		//		break;
		//	case (GL_FLOAT_VEC4):
		//		return new opengl_constant < vec4 > (location, id);
		//		break;
		//	case (GL_FLOAT_MAT4):
		//		return new opengl_constant < mat4 > (location, id);
		//		break;
		//	case (GL_SAMPLER_2D):
		//		return new opengl_constant < uint32_t > (location, id);
		//		break;
		//	}
		//
		//	return nullptr;
		//}

		uint8_t opengl_effect::run_id () { return _run_id; }
		
		void opengl_effect::load (
			const char * buffer, uint32_t length
		){
			gl_eval_scope(opengl_effect::load);
			
			_shader_program_id = glCreateProgram ();

			std::string
				vs_shader_source = "#version 330 core\n#define VERTEX_SHADER 1\n",
				fs_shader_source = "#version 330 core\n#define FRAGMENT_SHADER 1\n";

			vs_shader_source.append (buffer, length);
			fs_shader_source.append (buffer, length);
			
			GLint
				_vs_shader_id = glCreateShader (GL_VERTEX_SHADER),
				_fs_shader_id = glCreateShader (GL_FRAGMENT_SHADER);
			
			load_gl_shader (_vs_shader_id, vs_shader_source);
			load_gl_shader (_fs_shader_id, fs_shader_source);
			
			if (!(is_shader_ok(_vs_shader_id) && is_shader_ok(_fs_shader_id))) {
				debug_print("[ballistic::graphics::opengl_effect::load] GL Shader compilation failed. Shader program not loaded.");
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
				debug_print ("[ballistic::graphics::opengl_effect::load] GL Shader linking failed. Shader program not loaded");
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

				id_t id = text_to_id (name);

				_constants[id] = new opengl_constant(location, id);
			}
		}
		
		void opengl_effect::apply (idevice * device) {
			
			if (_shader_program_id == -1) {
				glUseProgram (0);
				return;
			}
			
			glUseProgram (_shader_program_id);

			// reset texture unit
			auto texture_unit = _constants[id::effect::texture];
			if (texture_unit)
				texture_unit->set_value (0);
		}

		iconstant * opengl_effect::constant(const id_t & id) {
			auto it = _constants.find(id);
			if (it != _constants.end ())
				return it->second;
			else
				return &null_constant::instance;
		}

		const map < id_t, iconstant * > & opengl_effect::constants () const {
			return _constants;
		}

	}
}