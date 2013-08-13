#ifndef _ballistic_graphics_imaterial_h_
#define	_ballistic_graphics_imaterial_h_

#include <ballistic.base.h>
#include <string>

#include "ballistic.graphics.material.h"
#include "ballistic.graphics.constant.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class ieffect : public ballistic::resources::iresource {
		public:

			virtual ihardware_constant * get_constant (id_t id) const = 0;

			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			) = 0;

			virtual void apply () = 0;

		};

	}
}

#endif