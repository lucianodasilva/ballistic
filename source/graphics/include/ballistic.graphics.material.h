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

			color		diffuse;
			itexture *	texture;
			bool		opaque;

			

		};

	}
}

#endif