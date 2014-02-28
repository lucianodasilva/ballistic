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

		class ieffect : public ballistic::iresource {
		public:

			virtual uint8_t run_id () = 0;

			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			) = 0;

			virtual void apply (idevice * device) = 0;

		};

	}
}

#endif