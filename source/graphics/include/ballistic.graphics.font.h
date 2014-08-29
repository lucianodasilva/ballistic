#ifndef	_ballistic_graphics_font_h_
#define _ballistic_graphics_font_h_

#include <ballistic.base.h>

#include "ballistic.graphics.material.h"

namespace ballistic {
	namespace graphics {

		class itexture;

		class font : public material {
		public:

			font (const id_t & id);

			vec2		font_metrics [256];

			static vec2	font_uv[256];

		};

	}
}

#endif