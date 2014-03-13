#ifndef	_ballistic_graphics_imaterial_h_
#define _ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class itexture;
		class ieffect;

		class idevice;

		class imaterial : public ballistic::iresource {
		public:

			imaterial (const id_t & id);

			virtual uint8_t		run_id () = 0;

			virtual void		effect (ieffect * effect) = 0;
			virtual ieffect *	effect () = 0;

			virtual void		diffuse (const color & v) = 0;
			virtual color		diffuse () = 0;

			virtual void		specular (const color & v) = 0;
			virtual color		specular () = 0;

			virtual void		opaque (bool v) = 0;
			virtual bool		opaque () = 0;

			virtual void		texture (itexture * v) = 0;
			virtual itexture *	texture () = 0;

			virtual void		apply (idevice * device) = 0;

		};

	}
}

#endif