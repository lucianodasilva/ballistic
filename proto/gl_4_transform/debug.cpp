#include "debug.h"


string debug::error_to_string (GLenum error) {
# define auto_case(x) \
		case x: \
			return #x;

	switch (error) {
		auto_case (GL_INVALID_ENUM)
		auto_case (GL_INVALID_VALUE)
		auto_case (GL_INVALID_OPERATION)
		auto_case (GL_INVALID_FRAMEBUFFER_OPERATION)
		auto_case (GL_OUT_OF_MEMORY)
		auto_case (GL_STACK_UNDERFLOW)
		auto_case (GL_STACK_OVERFLOW)
		auto_case (GL_NO_ERROR)
	default:
		return "Unknown error code!";
	};

# undef auto_case
}

void debug::eval_shader_compile (GLint shader_id) {

	GLint compiler_state;
	glGetShaderiv (shader_id, GL_COMPILE_STATUS, &compiler_state);
			
	if (compiler_state == GL_FALSE) {
		int
			info_length,
			writen_chars;
					
		char * info_log;
			
		glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_length);
		info_log = new char [info_length];
				
		glGetShaderInfoLog (shader_id, info_length, &writen_chars, info_log);
				
		string error (info_log, writen_chars);
		std::cerr << "GL Shader " << shader_id << " compile failed with error: " << error;
				
		delete [] info_log;
	}
}

void debug::eval_program_link (GLint program_id) {
	GLint link_state;
	glGetProgramiv (program_id, GL_LINK_STATUS, &link_state);
	if (link_state == GL_FALSE) {
		int
			info_length,
			writen_chars;
					
		char * info_log;
			
		glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_length);
		info_log = new char [info_length];
				
		glGetProgramInfoLog (program_id, info_length, &writen_chars, info_log);
				
		string error (info_log, writen_chars);
		std::cerr << "GL Program " << program_id << " link failed with error: " << error;
				
		delete [] info_log;
	}
}

debug::eval_scope::~eval_scope () {
	GLenum error = glGetError ();
	if (error != GL_NO_ERROR)
		std::cerr << "GL Scope [" << method_name << "] Failed in file " << __FILE__ << " with " << debug::error_to_string (error) ;
}