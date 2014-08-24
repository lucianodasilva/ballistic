#ifndef	_ballistic_graphics_opengl_effect_h_
#define _ballistic_graphics_opengl_effect_h_

#include <ballistic.graphics.h>
#include <GL/glew.h>

#include <map>
#include <limits>

using namespace std;

namespace ballistic {
	namespace graphics {

		// would be fun if in debug had 
		// type validation... just saying
		struct opengl_constant : public iconstant {

			GLuint	location;
			id_t	id;

			inline opengl_constant (GLuint location_v, const id_t & id_v) : location (location_v), id (id_v) {}

			inline void set_value (uint32_t v) override {
				glUniform1ui (location, v);
			}

			inline void set_value (int32_t v) override {
				glUniform1i (location, v);
			}

			inline void set_value (real v) override {
				glUniform1f (location, v);
			}

			inline void set_value (const vec2 & v) override {
				glUniform2f (location, v.x, v.y);
			}

			inline void set_value (const vec3 & v) override {
				glUniform3f (location, v.x, v.y, v.z);
			}

			inline void set_value (const vec4 & v) override {
				glUniform4f (location, v.x, v.y, v.z, v.w);
			}

			inline void set_value (const color & v) override {
				glUniform4f (location, v.r, v.g, v.b, v.a);
			}

			inline void set_value (const mat4 & v) override {
				glUniformMatrix4fv (location, 1, false, (GLfloat *)&v);
			}
		
		};

		class opengl_effect : public ballistic::graphics::ieffect {
		private:

			map < id_t, iconstant * > _constants;
			
			GLint _shader_program_id;

			uint8_t _run_id;
			
			static bool is_shader_ok (GLint shader_id);
			static bool is_link_ok (GLint program_id);
			
			static void load_gl_shader (GLint shader_id, const string & source);

			static iconstant * create_constant (GLuint location, const id_t & id, GLuint type);

		public:
			
			opengl_effect (const id_t & id, uint8_t run_id);
			virtual ~opengl_effect ();

			virtual uint8_t run_id ();
			
			virtual void load (
				const char * buffer,
				uint32_t length
			);
			
			virtual void apply (idevice * device);

			virtual iconstant * constant(const id_t & id);
			virtual const map < id_t, iconstant * > & constants () const override;

		};

	}
}

#endif