#ifndef _ballistic_graphics_imaterial_h_
#define	_ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

#include "ballistic.graphics.material.h"
#include "ballistic.graphics.ieffectfield.h"

namespace ballistic {
	namespace graphics {

		class ieffect : public ballistic::resources::iresource {
		public:

			virtual ieffectfield * get_uniform_id () = 0;


			virtual void apply () = 0;

		};

	}
}

#endif