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

			opengl_material		(uint8_t run_id);

			virtual uint8_t		get_run_id ();

			virtual void		set_effect (ieffect * effect);
			virtual ieffect *	get_effect ();

			virtual void		set_diffuse (const color & v);
			virtual color		get_diffuse ();

			virtual void		set_specular (const color & v);
			virtual color		get_specular ();

			virtual void		set_opaque ( bool v );
			virtual bool		get_opaque ();

			virtual void		set_texture (itexture * v);
			virtual itexture *	get_texture ();

			virtual void		apply (idevice * device);


		};

	}
}

#endif //!_ballistic_graphics_opengl_material_h_
