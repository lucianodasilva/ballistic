#ifndef	_debug_h_
#define _debug_h_

#include <GL/glew.h>
#include <string>
#include <iostream>

using namespace std;

#	define gl_shader_source(x) \
	"#version 330 core\n" \
	#x


#	define gl_eval(x) \
		x; \
		{ \
			GLenum error = glGetError (); \
			if (error != GL_NO_ERROR) \
				std::_Cou ("GL Call [" << #x << "] Failed in file " << __FILE__ << " at line " << __LINE__ << " with " << debug::error_to_string (error) ); \
		}

#	define gl_eval_shader_compile(shader_id) \
		debug::eval_shader_compile (shader_id)

#	define gl_eval_program_link(program_id) \
		debug::eval_program_link (program_id);

#	define gl_eval_scope(scope_name) \
	debug::eval_scope __gl_evaluate_scope__ = {#scope_name}

class debug {
public:

	// generic tools
	static string error_to_string (GLenum error);

	static void eval_shader_compile (GLint shader_id);

	static void eval_program_link (GLint program_id);

	struct eval_scope {
		string method_name;
		~eval_scope ();
	};

};

#endif