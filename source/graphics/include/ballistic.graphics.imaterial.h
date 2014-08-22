#ifndef	_ballistic_graphics_imaterial_h_
#define _ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {

		class itexture;
		class ieffect;

		class idevice;

		class imaterial : public ballistic::iresource {
		public:

			imaterial (const id_t & id);

			virtual void		effect (ieffect * effect) = 0;
			virtual ieffect *	effect () const = 0;

			virtual void		diffuse (const color & v) = 0;
			virtual color		diffuse () const = 0;

			virtual void		texture(itexture * v) = 0;
			virtual itexture *	texture() const = 0;

			virtual void		opaque (bool v) = 0;
			virtual bool		opaque () const = 0;

			virtual void		apply (idevice * device) = 0;

		};

	}
}

#endif