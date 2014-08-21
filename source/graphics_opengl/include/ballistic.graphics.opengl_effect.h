#ifndef	_ballistic_graphics_opengl_effect_h_
#define _ballistic_graphics_opengl_effect_h_

#include <ballistic.graphics.h>
#include <GL/glew.h>

#include <map>
#include <limits>

using namespace std;

namespace ballistic {
	namespace graphics {

		template < class value_t >
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

			inline virtual imaterial_property * create_property () override {
				auto new_prop = new material_property < value_t >(id, value_t());
				new_prop->constant(this);

				return new_prop;
			}
		
		};

		struct opengl_constant_old {
			GLuint	location;
			id_t	id;

			inline opengl_constant_old () : location (std::numeric_limits < GLuint >::max ()), id (0) {}
			inline opengl_constant_old (const opengl_constant_old & c) : location (c.location), id (c.id) {}
			inline opengl_constant_old (GLuint location_v, id_t id_v) : location (location_v), id (id_v) {}

			inline bool is_defined () const {
				return location != std::numeric_limits < GLuint >::max ();
			}

			inline opengl_constant_old & operator = ( opengl_constant_old v ) {
				location = v.location;
				id = v.id;

				return *this;
			}

		};

		class opengl_effect : public ballistic::graphics::ieffect {
		private:

			vector < iconstant * > _constants;
			
			GLint _shader_program_id;

			uint8_t _run_id;

			// -

			typedef map < id_t, opengl_constant_old > constant_map_t;

			// DEPRECATED
			constant_map_t _constants_old;

			// -
			
			static bool is_shader_ok (GLint shader_id);
			static bool is_link_ok (GLint program_id);
			
			static void load_gl_shader (GLint shader_id, const string & source);

			static iconstant * create_constant (GLuint location, const id_t & id, GLuint type);

		public:
			
			opengl_effect (const id_t & id, uint8_t run_id);
			virtual ~opengl_effect ();

			virtual uint8_t run_id ();

			virtual opengl_constant_old constant (id_t id) const;
			
			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			);
			
			virtual void apply (idevice * device);

			// DEPRECATED
			void constant (opengl_constant_old & u, int32_t v);
			void constant (opengl_constant_old & u, real v);
			void constant (opengl_constant_old & u, const vec2 & v);
			void constant (opengl_constant_old & u, const vec3 & v);
			void constant (opengl_constant_old & u, const vec4 & v);
			void constant (opengl_constant_old & u, const mat4 & v);
			void constant (opengl_constant_old & u, const color & v);

			virtual const vector < iconstant * > & constants () const override;

		};

	}
}

#endif