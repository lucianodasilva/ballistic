#ifndef	_ballistic_graphics_imaterial_h_
#define _ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {

		class itexture;
		class ieffect;

		class idevice;

		class material : public ballistic::iresource {
		public:

			material (const id_t & id);
			virtual ~material();

			color		
				diffuse,
				color_mask,
				ambient_sky,
				ambient_ground;

			real		
				specular_hardness,
				specular_intensity,
				ambient_intensity,
				opacity;

			bool
				blended;

			itexture *	texture;

		};

	}
}

#endif