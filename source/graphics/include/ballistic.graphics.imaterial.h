#ifndef	_ballistic_graphics_imaterial_h_
#define _ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class itexture;
		class ieffect;

		class imaterial : public resources::iresource {
		public:

			virtual uint8		get_run_id () = 0;

			virtual void		set_effect (ieffect * effect) = 0;
			virtual ieffect *	get_effect () = 0;

			virtual void		set_diffuse (const color & v) = 0;
			virtual color		get_diffuse () = 0;

			virtual void		set_specular (const color & v) = 0;
			virtual color		get_specular () = 0;

			virtual void		set_opaque (bool v) = 0;
			virtual bool		get_opaque () = 0;

			virtual void		set_texture (itexture * v) = 0;
			virtual itexture *	get_texture () = 0;

			virtual void		apply () = 0;

		};

	}
}

#endif