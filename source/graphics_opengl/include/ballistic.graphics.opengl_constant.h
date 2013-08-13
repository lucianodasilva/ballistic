
#ifndef _ballistic_graphics_opengl_constant_h_
#define _ballistic_graphics_opengl_constant_h_

#include <ballistic.graphics.h>

#include "ballistic.graphics.opengl_debug.h"

namespace ballistic {
	namespace graphics {

		struct opengl_uniform_setter {

			template < class T >
			static inline void set_uniform (GLuint location, T & value) {
				//static_assert (false, "Constant type not supported!");
				debug_error ("GL Constant type not supported");
			}

			static inline void set_uniform (GLuint location, int32 & value) {
				gl_eval_scope (opengl_uniform_setter::set_uniform <int32>);
				glUniform1i (location, value);
			}

			static inline void set_uniform (GLuint location, real & value) {
				gl_eval_scope (opengl_uniform_setter::set_uniform <real>);
				glUniform1f (location, value);
			}

			static inline void set_uniform (GLuint location, vec3 & value) {
				gl_eval_scope (opengl_uniform_setter::set_uniform <vec3>);
				glUniform3fv (location, 1, (GLfloat *)&value);
			}

			static inline void set_uniform (GLuint location, vec4 & value) {
				gl_eval_scope (opengl_uniform_setter::set_uniform <vec4>);
				glUniform4fv (location, 1, (GLfloat *)&value);
			}

			static inline void set_uniform (GLuint location, mat4 & value) {
				gl_eval_scope (opengl_uniform_setter::set_uniform <mat4>);
				glUniformMatrix4fv (location, 16, false, (GLfloat *)&value);
			}
		};
		
		template < class T >
		class opengl_constant : public ihardware_constant_base < T > {
		private:

			GLuint _location;

		public:
			
			inline opengl_constant (id_t id, GLuint location) : _location (location) {
				ihardware_constant_base < T >::_id = id;
			}
			
			virtual inline void apply () {
				opengl_uniform_setter::set_uniform (_location, ihardware_constant_base < T >::_value);
			}

		};

	}
}

#endif
