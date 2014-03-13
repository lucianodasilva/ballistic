#ifndef _ballistic_graphics_opengl_material_h_
#define _ballistic_graphics_opengl_material_h_

#include <ballistic.graphics.h>

#include "ballistic.graphics.opengl_effect.h"

namespace ballistic {
	namespace graphics {

		class opengl_material : public imaterial {
		private:

			color				_diffuse;
			opengl_constant		_diffuse_constant;

			color				_specular;
			opengl_constant		_specular_constant;

			bool				_opaque;

			itexture *			_texture;

			opengl_effect *		_effect;

			uint8_t				_run_id;
		
		public:

			opengl_material		(const id_t & id, uint8_t run_id);

			virtual uint8_t		run_id ();

			virtual void		effect (ieffect * effect);
			virtual ieffect *	effect ();

			virtual void		diffuse (const color & v);
			virtual color		diffuse ();

			virtual void		specular (const color & v);
			virtual color		specular ();

			virtual void		opaque ( bool v );
			virtual bool		opaque ();

			virtual void		texture (itexture * v);
			virtual itexture *	texture ();

			virtual void		apply (idevice * device);


		};

	}
}

#endif //!_ballistic_graphics_opengl_material_h_
