#ifndef _ballistic_graphics_ieffect_h_
#define	_ballistic_graphics_ieffect_h_

/*
	Supported shader keywords

	effect_diffuse
	effect_specular
	effect_t_model
	effect_t_view
	effect_t_proj


*/

#include <ballistic.base.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;
		class imaterial_property;

		class iconstant {
		public:

			virtual void set_value (uint32_t v) = 0;
			virtual void set_value (int32_t v) = 0;
			virtual void set_value (real v) = 0;
			virtual void set_value (const vec2 & v) = 0;
			virtual void set_value (const vec3 & v) = 0;
			virtual void set_value (const vec4 & v) = 0;
			virtual void set_value (const mat4 & v) = 0;
			virtual void set_value (const color & v) = 0;

		};

		class ieffect : public ballistic::iresource {
		public:

			ieffect (const id_t & id);

			virtual uint8_t run_id () = 0;

			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			) = 0;

			virtual void apply (idevice * device) = 0;

			virtual iconstant * constant(const id_t & id) = 0;
			virtual const map < id_t, iconstant * > & constants () const = 0;

		};

	}
}

#endif