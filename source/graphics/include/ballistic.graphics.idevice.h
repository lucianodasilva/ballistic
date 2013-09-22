#ifndef	_ballistic_graphics_idevice_h_
#define _ballistic_graphics_idevice_h_

#include <ballistic.base.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

		class ieffect;
		class imaterial;
		class imesh;
		class itexture;

		class idevice {
		public:

			// Resources ----------------
			virtual ieffect *	create_effect () = 0;
			virtual imaterial * create_material () = 0;
			virtual imesh *		create_mesh () = 0;
			virtual itexture *	create_texture (const point & size) = 0;
			// ---------------------------

			virtual void		activate (ieffect * effect) = 0;
			virtual void		activate (imaterial * material) = 0;
			virtual void		activate (imesh * mesh) = 0;

			// ---------------------------

			virtual void		set_clear_color ( const color & cr ) = 0;

			virtual void 		set_view (const mat4 & view) = 0;
			virtual const mat4 & get_view () const = 0;

			virtual void		set_model (const mat4 & model) = 0;
			virtual const mat4 & get_model () const = 0;

			virtual void		set_proj (const mat4 & proj) = 0;
			virtual const mat4 & get_proj () const = 0;

			virtual void		clear () = 0;

			virtual void		begin_frame () = 0;
			virtual void		end_frame () = 0;
	
			virtual void		present () = 0;

			virtual void		destroy () = 0;

			virtual void		draw_active_mesh (const mat4 transform) = 0;
		};

	}
}

#endif