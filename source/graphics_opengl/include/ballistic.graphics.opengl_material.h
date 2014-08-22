#ifndef _ballistic_graphics_opengl_material_h_
#define _ballistic_graphics_opengl_material_h_

#include <ballistic.graphics.h>

#include "ballistic.graphics.opengl_effect.h"

namespace ballistic {
	namespace graphics {

		class opengl_material : public imaterial {
		private:

			color				_diffuse;
			iconstant *			_diffuse_constant;

			bool				_opaque;

			itexture *			_texture;

			opengl_effect *		_effect;

		
		public:

			opengl_material		(const id_t & id);

			virtual void		effect (ieffect * effect);
			virtual ieffect *	effect () const;

			virtual void		diffuse (const color & v);
			virtual color		diffuse () const;

			virtual void		opaque ( bool v );
			virtual bool		opaque() const;

			virtual void		texture (itexture * v);
			virtual itexture *	texture () const;

			virtual void		apply (idevice * device);


		};

	}
}

#endif //!_ballistic_graphics_opengl_material_h_
