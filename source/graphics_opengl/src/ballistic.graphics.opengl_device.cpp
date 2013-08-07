#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>

#include "ballistic.graphics.opengl_mesh.h"

namespace ballistic {
	namespace graphics {

//		GLenum
//			_shader_program,
//			_vs_shader,
//			_ps_shader;
//		
//		struct joint {
//			vec3 p;
//			quat r;
//			
//			inline joint to_absolute ( const joint & parent ) {
//				return joint {
//					parent.p + (parent.r * p),
//					parent.r * r
//				};
//			}
//		};
//		
//		struct skinned_vector {
//			vec3 position;
//			vec2 uv;
//			real bias;
//			uint16 bone_a;
//			uint16 bone_b;
//		};
//		
//		real angle = 0.0;
//		real angle_inc = 0.0005;
//		
//		GLint
//			_proj_location,
//			_model_location;
//		
//		joint bones [] = {
//			{
//				vec3 (.0, .0, .0),
//				quat::from_axis(vec3 (.0, .0, 1), .0)
//			},
//			{
//				vec3 (.0, .2, .0),
//				quat::from_axis(vec3 (.0, .0, 1), .0)
//			},
//			{
//				vec3 (.0, .2, .0),
//				quat::from_axis(vec3 (.0, .0, 1), .0)
//			},
//			{
//				vec3 (.0, .2, .0),
//				quat::from_axis(vec3 (.0, .0, 1), .0)
//			},
//			{
//				vec3 (.0, .2, .0),
//				quat::from_axis(vec3 (.0, .0, 1), .0)
//			},
//		};
		
		/*
		skinned_vector skin_buffer [] {
			{{-.1, .0, .0},{.0,.0}, .0, 0, 0},
			{{.1, .0, .0},{.0,.0}, .0, 0, 0},
			{{-.1, .19, .0},{.0,.0}, .9, 0, 1},
			{{.1, .19, .0},{.0,.0}, .9, 0, 1},
			{{-.1, .21, .0},{.0,.0}, .1, 1, 2},
			{{.1, .21, .0},{.0,.0}, .1, 1, 2},
			{{-.1, .39, .0},{.0,.0}, .9, 1, 2},
			{{.1, .39, .0},{.0,.0}, .9, 1, 2},
			{{-.1, .41, .0},{.0,.0}, .1, 2, 3},
			{{.1, .41, .0},{.0,.0}, .1, 2, 3},
			{{-.1, .59, .0},{.0,.0}, .9, 2, 3},
			{{.1, .59, .0},{.0,.0}, .9, 2, 3,},
			{{-.1, .61, .0},{.0,.0}, .1, 3, 4},
			{{.1, .61, .0},{.0,.0}, .1, 3, 4},
			{{-.1, .79, .0},{.0,.0}, .9, 3, 4},
			{{.1, .79, .0},{.0,.0}, .9, 3, 4,},
			{{-.1, .8, .0},{.0,.0}, .0, 4, 0},
			{{.1, .8, .0},{.0,.0}, .0, 4, 0}
		};
		 */

		string gl_error_to_string ( GLenum error ) {
#			define auto_case(x) \
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

#			undef auto_case
		}
		
#		define gl_eval(x) \
			x; \
			{ \
				GLenum error = glGetError (); \
				if (error != GL_NO_ERROR) \
					debug_warn ("GL Call [" << #x << "] Failed at line " << __LINE__ << " failed with " << gl_error_to_string (error) ); \
			}
		
#		define gl_shader(x) \
			"#version 330 core\n" \
			#x;
		
		struct cvec {
			vec3 position;
			vec4 color;
		};
		
		cvec vec_buffer [] = {
			{vec3 (-1., -1., .0),	vec4 (1., .0, .0, 1.)},
			{vec3 (1., -1., .0),	vec4 (.0, 1., .0, 1.)},
			{vec3 (.0, 1. ,.0),		vec4 (.0, .0, 1., 1.)}
		};
		
		uint16 index_buffer [] = {
			0, 1, 2
		};
		
		uint32
			_vertex_array_id,
			_vertex_buffer_id,
			_index_buffer_id,
			_shader_program,
			_vertex_program,
			_pixel_program;
		
		bool load_shader ( const std::string & source, uint32 id ) {
			const char * source_ptr = source.c_str ();
			
			int32 length = source.length ();
			glShaderSource (id, 1, (const GLchar **)&source_ptr, &length);
			
			glCompileShader (id);
			
			GLint compiler_state;
			glGetShaderiv (id, GL_COMPILE_STATUS, &compiler_state);
			if (compiler_state == GL_FALSE) {
				int32
					info_length,
					writen_chars;
					
				char * info_log;
			
				glGetShaderiv (id, GL_INFO_LOG_LENGTH, &info_length);
				info_log = new char [info_length];
				
				glGetShaderInfoLog (id, info_length, &writen_chars, info_log);
				
				string error (info_log, writen_chars);
				debug_error("shader compile error: " << error);
				
				delete info_log;
				return false;
			}
			
			return true;
		}

		opengl_device::opengl_device () : _current_mesh (nullptr) {
			glewExperimental = true;
			
			GLenum init_error = glewInit();
			if (init_error != GLEW_OK) {
				debug_error ("glew initialization error: " << glewGetErrorString(init_error));
			}
			
			glGetError (); // reset errors
			
			string gl_str_version = (const char *) glGetString (GL_VERSION);
			
			debug_warn ("OpenGL version: " << gl_str_version);
			
			_vertex_buffer_id = 0;
			_index_buffer_id = 0;
			
			// Create vertex buffer
			gl_eval (glGenBuffers (1, &_vertex_buffer_id));
			gl_eval (glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id));
			gl_eval (glBufferData( GL_ARRAY_BUFFER, 4 * 7 * 3, (GLvoid *)&vec_buffer [0], GL_STATIC_DRAW));
			
			// Create index buffer
			gl_eval (glGenBuffers (1, &_index_buffer_id));
			gl_eval (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id));
			gl_eval (glBufferData (GL_ELEMENT_ARRAY_BUFFER, 2 * 3, (GLvoid *)&index_buffer, GL_STATIC_DRAW));
			
			// unbind buffers
			gl_eval(glBindBuffer (GL_ARRAY_BUFFER, 0));
			gl_eval(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
			
			// create and setup vao
			gl_eval(glGenVertexArrays (1, &_vertex_array_id));
			gl_eval(glBindVertexArray (_vertex_array_id));
			
			gl_eval(glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id));
			
			// position
			gl_eval (
				glVertexAttribPointer(
				   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				   3,                  // size
				   GL_FLOAT,           // type
				   GL_FALSE,           // normalized?
				   4 * 7,                  // stride
				   (void*)0            // array buffer offset
				);
			);
			gl_eval(glEnableVertexAttribArray (0));
			
			// color
			gl_eval (
				glVertexAttribPointer(
					1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					4,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					4 * 7,              // stride
					(void*)(4 * 3)      // array buffer offset
				);
			);
			gl_eval(glEnableVertexAttribArray (1));
			
			gl_eval(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id));
			
			// reset state machine
			gl_eval (glBindVertexArray (0));
			gl_eval (glDisableVertexAttribArray (0));
			gl_eval (glDisableVertexAttribArray (1));
			gl_eval (glBindBuffer (GL_ARRAY_BUFFER, 0));
			gl_eval (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
			
			// -------------------------
			_shader_program = glCreateProgram ();
			_vertex_program = glCreateShader (GL_VERTEX_SHADER);
			_pixel_program = glCreateShader (GL_FRAGMENT_SHADER);
			
			std::string vertex_source = 
			gl_shader (
				layout (location = 0) in vec3 in_position;
				layout (location = 1) in vec4 in_color;

				out vec4 var_color;

				void main () {
					gl_Position.xyz = in_position;
					gl_Position.w = 1.0;

					var_color = in_color;
				}
			);
			
			std::string frag_source =
			gl_shader (
				in vec4		var_color;
				out vec4	out_color;

				void main () {
					out_color = var_color;
				}
			);
			
			if (!load_shader (vertex_source, _vertex_program))
				return;
			
			if (!load_shader (frag_source, _pixel_program))
				return;
			
			gl_eval (glAttachShader (_shader_program, _vertex_program));
			gl_eval (glAttachShader (_shader_program, _pixel_program));
			
			gl_eval (glLinkProgram (_shader_program));

			GLint link_state;
			glGetProgramiv (_shader_program, GL_LINK_STATUS, &link_state);
			if (link_state == GL_FALSE) {
				int32
					info_length,
					writen_chars;
					
				char * info_log;
			
				glGetProgramiv (_shader_program, GL_INFO_LOG_LENGTH, &info_length);
				info_log = new char [info_length];
				
				glGetProgramInfoLog (_shader_program, info_length, &writen_chars, info_log);
				
				string error (info_log, writen_chars);
				debug_error("shader link error: " << error);
				
				delete info_log;
			}
	
			gl_eval (glDeleteShader (_vertex_program));
			gl_eval (glDeleteShader (_pixel_program));
			
//			glDisable(GL_CULL_FACE);
//			
//			// setup
//			glGenBuffers (1, &_vertex_buffer_id);
//			glGenBuffers (1, &_index_buffer_id);
//			
//			// Interleaved vertex buffer
//			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
//			glBufferData (GL_ARRAY_BUFFER, sizeof (vec_buffer), (GLvoid *)&vec_buffer[0], GL_STATIC_DRAW);
//			
//			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
//			glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (skin_index_buffer), (GLvoid *)&skin_index_buffer[0], GL_STATIC_DRAW);
//
//			// enable shader program
//			_shader_program = glCreateProgram ();
//			_vs_shader = glCreateShader (GL_VERTEX_SHADER);
//			_ps_shader = glCreateShader (GL_FRAGMENT_SHADER);
//			
//			std::string vertex_source =
//				"#version 330 core\n"
//				"layout (location = 0) in vec3 in_vertex;"
//				""
//				"uniform mat4 in_projection_matrix;"
//				"uniform mat4 in_modelview_matrix;"
//				""
//				"void main (void) {"
//				"	vec4 v_pos = in_projection_matrix * in_modelview_matrix * vec4(in_vertex, 1.0);"
//				"	v_pos.x += 0.2;"
//				"	gl_Position = v_pos;"
//				"}"
//			;
//			
//			std::string pixel_source =
//			"#version 330 core\n"
//			"out vec4 out_color;"
//			""
//			"void main (void) {"
//			"	out_color = vec4 (0.0, 1.0, 0.0, 1.0);"
//			"}"
//			;
//
//			const char * source_char_ptr = vertex_source.c_str ();
//			int vertex_length = vertex_source.length ();
//			
//			glShaderSource (_vs_shader, 1, (const GLchar **)&source_char_ptr, &vertex_length);
//			
//			source_char_ptr = pixel_source.c_str ();
//			int pixel_length = pixel_source.length ();
//			
//			glShaderSource (_ps_shader, 1, (const GLchar **)&source_char_ptr, &pixel_length);
//			
//			glCompileShader (_vs_shader);
//			glCompileShader (_ps_shader);
//			GLint compiler_state;
//			
//			glGetShaderiv (_vs_shader, GL_COMPILE_STATUS, &compiler_state);
//			if (compiler_state == GL_FALSE) {
//				
//				int32
//					info_length,
//					writen_chars;
//				
//				char * info_log;
//				
//				glGetShaderiv (_vs_shader, GL_INFO_LOG_LENGTH, &info_length);
//				info_log = new char [info_length];
//				
//				glGetShaderInfoLog (_vs_shader, info_length, &writen_chars, info_log);
//				
//				string error (info_log, writen_chars);
//				
//				debug_error("vertex shader compile error: " << error);
//				
//				delete info_log;
//			}
//			
//			glGetShaderiv (_ps_shader, GL_COMPILE_STATUS, &compiler_state);
//			if (compiler_state == GL_FALSE) {
//				
//				int32
//				info_length,
//				writen_chars;
//				
//				char * info_log;
//				
//				glGetShaderiv (_ps_shader, GL_INFO_LOG_LENGTH, &info_length);
//				info_log = new char [info_length];
//				
//				glGetShaderInfoLog (_ps_shader, info_length, &writen_chars, info_log);
//				
//				string error (info_log, writen_chars);
//				
//				debug_error("pixel shader compile error: " << error);
//				
//				delete info_log;
//			}
//			
//			glAttachShader (_shader_program, _vs_shader);
//			glAttachShader (_shader_program, _ps_shader);
//			
//			glBindAttribLocation (_shader_program, 0, "in_vertex");
//			
//			glLinkProgram (_shader_program);
//			
//			_proj_location = glGetUniformLocation (_shader_program, "in_projection_matrix");
//			_model_location = glGetUniformLocation (_shader_program, "in_modelview_matrix");
//			
//			glUseProgram (_shader_program);
		}
	
		imaterial * opengl_device::create_material ()
		{
			return nullptr;
		}
		
		imesh *	opengl_device::create_mesh ()
		{
			return new opengl_mesh ();
		}
		
		itexture * opengl_device::create_texture (const point & size)
		{
			return nullptr;
		}
		
		imaterial * opengl_device::load_material ( const string & filename )
		{
			return nullptr;
		}
		
		imesh *	opengl_device::load_mesh ( const string & filename )
		{
			return nullptr;
		}
		
		itexture * opengl_device::load_texture ( const string & filename )
		{
			return nullptr;
		}
		
		void opengl_device::set_transform(const mat4 & matrix)
		{
			//glUniformMatrix4fv (_model_location, 1, GL_FALSE, &matrix.data[0]);
			
			//glMatrixMode(GL_MODELVIEW);
			//glLoadMatrixf (&matrix.data [0]);
		}
		
		void opengl_device::set_projection ( const mat4 & matrix ) {
			//glUniformMatrix4fv (_proj_location, 1, GL_FALSE, &matrix.data [0]);
			//glMatrixMode(GL_PROJECTION);
			//glLoadTransposeMatrixf (&matrix.data [0]);
		}

		void opengl_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void opengl_device::clear () {
			glClearColor (
				_clear_color.r,
				_clear_color.g,
				_clear_color.b,
				_clear_color.a
			);

			glClear (GL_COLOR_BUFFER_BIT);
		}

		mat4 create_ortho (real left, real right, real bottom, real top, real near, real far) {
			return mat4 ( 
				2.0 / ( right - left ), .0, .0, -((right + left)/(right - left)),
				.0, 2.0 / ( top - bottom ), .0, -((top + bottom) / ( top - bottom)),
				.0, .0, -2 / ( far - near ), - ((far + near) / ( far - near)),
				.0, .0, .0, 1.0
			);
		}
		
		void opengl_device::begin_frame ()
		{
			glClear(GL_DEPTH_BUFFER_BIT);			
		}

//		void draw_line (const vec3 & v1, const vec3 & v2) {
//			glBegin (GL_LINES);
//			glVertex3f (v1.x, v1.y, v1.z);
//			glVertex3f (v2.x, v2.y, v2.z);
//			glEnd ();
//		}
//
//		void draw_joint (const joint & parent, const joint & child ) {
//			glColor3f (1., .0, .0);
//
//			draw_line (parent.p, child.p);
//
//			glColor3f (.0, 1., .0);
//			
//			draw_line (parent.p + vec3 (-.01, .0, .0), parent.p + vec3 (.01, .0, .0));
//			draw_line (parent.p + vec3 (0, -.01, .0), parent.p + vec3 (.0, .01, .0));
//		}
		
		void opengl_device::end_frame ()
		{
			gl_eval(glUseProgram (_shader_program));

			gl_eval(glBindVertexArray (_vertex_array_id));
			
			gl_eval(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));
			
			gl_eval(glBindVertexArray (0));

			//glBindBuffer (GL_ARRAY_BUFFER, 0);
			//glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
			
			//glDisableVertexAttribArray (0);
			
			//glLoadIdentity();

			// draw skin

//			glUseProgram (_shader_program);
//			
//			mat4 t;
//			//mat4 proj = camera::make_projection(-1., 1., 1., -1., .0, 1000.0);
//			mat4 proj = create_ortho(-1., 1., -1., 1., -1.0, 1000.);
//			
//			glUniformMatrix4fv (_model_location, 1, GL_FALSE, &t.data[0]);
//			glUniformMatrix4fv (_proj_location, 1, GL_FALSE, &proj.data[0]);
//
//			
//			
//			//glEnableClientState(GL_VERTEX_ARRAY);
//			//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//			
//			//glVertexPointer (3, GL_FLOAT, sizeof (skinned_vector), 0);
//			//glTexCoordPointer (2, GL_FLOAT, sizeof (skinned_vector), (GLvoid *)sizeof (vec3));
//			
//			glEnableVertexAttribArray(0);
//			glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id);
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//			
//			
//			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
//			
//			glColor3f(.0, .1, 1.);
//			glDrawElements (GL_TRIANGLES, sizeof (skin_index_buffer), GL_UNSIGNED_SHORT, 0);

			//glDisableVertexAttribArray (0);
			//glDisableClientState(GL_VERTEX_ARRAY);
			//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
			//glBindBuffer (GL_VERTEX_ARRAY, 0);
			//glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

			//glUseProgram (0);
			
			// ---------
			
			// handle bones
			
			//joint abones [sizeof (bones) / sizeof (joint)];
			
			//quat rotation = quat::from_axis (
			//								 vec3 (.0, .0, 1.0),
			//								 angle
			//								 );
			
			//abones [0].p = bones [0].p;
			//abones [0].r = rotation;
			
			//for ( int i = 1; i < sizeof (bones) / sizeof (joint); i++) {
			//	bones [i].r = rotation;
			//	abones [i] = bones [i].to_absolute(abones[i-1]);
				
			//	draw_joint (abones [i-1], abones[i]);
			//}
			
			// ---------

			//glFlush ();
			
			//angle += angle_inc;
			
			//if (angle > 1.2 || angle < -1.2)
			//	angle_inc *= -1.0;
				
			// ----------
			//glFlush ();
		}
		
		void opengl_device::set_current_mesh ( imesh * mesh )
		{
			if (mesh == _current_mesh)
				return;

			if (_current_mesh)
				_current_mesh->detach ();

			_current_mesh = mesh;
			_current_mesh->attach ();
		}

		imesh * opengl_device::get_current_mesh () {
			return _current_mesh;
		}
		
		void opengl_device::set_current_texture ( itexture * texture )
		{
		
		}
		
		void opengl_device::present ()
		{
		
		}
		
		void opengl_device::destroy ()
		{
		
		}
	
	}
}