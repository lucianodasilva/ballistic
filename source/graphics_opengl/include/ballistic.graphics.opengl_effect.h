#ifndef	_ballistic_graphics_opengl_effect_h_
#define _ballistic_graphics_opengl_effect_h_

#include <ballistic.graphics.h>
#include <GL/glew.h>

#include <map>
#include <limits>

using namespace std;

namespace ballistic {
	namespace graphics {

		struct opengl_constant {
			GLuint	location;
			id_t	id;

			inline opengl_constant () : location (std::numeric_limits < GLuint >::max ()), id (0) {}
			inline opengl_constant (const opengl_constant & c) : location (c.location), id (c.id) {}
			inline opengl_constant (GLuint location_v, id_t id_v) : location (location_v), id (id_v) {}

			inline bool is_defined () const {
				return location != std::numeric_limits < GLuint >::max ();
			}

			inline opengl_constant & operator = ( opengl_constant v ) {
				location = v.location;
				id = v.id;

				return *this;
			}

		};

		class opengl_effect : public ballistic::graphics::ieffect {
		private:
			
			GLint _shader_program_id;

			uint8_t _run_id;

			// -

			typedef map < id_t, opengl_constant > constant_map_t;

			constant_map_t _constants;

			// -
			
			bool is_shader_ok (GLint shader_id);
			bool is_link_ok (GLint program_id);
			
			void load_gl_shader (GLint shader_id, const string & source);

		public:
			
			opengl_effect (id_t id, uint8_t run_id);
			~opengl_effect ();

			virtual uint8_t run_id ();

			virtual opengl_constant constant (id_t id) const;
			
			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			);
			
			virtual void apply (idevice * device);

			void constant (opengl_constant & u, int32_t v);
			void constant (opengl_constant & u, real v);
			void constant (opengl_constant & u, const vec2 & v);
			void constant (opengl_constant & u, const vec3 & v);
			void constant (opengl_constant & u, const vec4 & v);
			void constant (opengl_constant & u, const mat4 & v);
			void constant (opengl_constant & u, const color & v);

		};

	}
}

#endif