#ifndef	_ballistic_graphics_opengl_effect_h_
#define _ballistic_graphics_opengl_effect_h_

#include <ballistic.graphics.h>
#include <gl/glew.h>

#include <map>

using namespace std;

namespace ballistic {
	namespace graphics {

		class opengl_effect : public ballistic::graphics::ieffect {
		private:
			
			GLint _shader_program_id;

			// -

			typedef map < id_t, ihardware_constant * > constant_map_t;

			constant_map_t _constants;

			// -
			
			bool is_shader_ok (GLint shader_id);
			bool is_link_ok (GLint program_id);
			
			void load_gl_shader (GLint shader_id, const string & source);

		public:
			
			opengl_effect ();
			~opengl_effect ();

			virtual ihardware_constant * get_constant (id_t id) const;
			
			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			);
			
			virtual void apply ();

		};

	}
}

#endif