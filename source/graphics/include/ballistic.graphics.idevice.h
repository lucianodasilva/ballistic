#ifndef	_ballistic_graphics_idevice_h_
#define _ballistic_graphics_idevice_h_

#include <ballistic.base.h>
#include <string>

#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.itexture.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice {
		public:

			virtual imesh *		create_mesh () = 0;
			virtual itexture *	create_texture (const point & size) = 0;

			virtual imesh *		load_mesh ( const string & filename ) = 0;
			virtual itexture *	load_texture ( const string & filename ) = 0;
			
			virtual void		set_transform ( const mat4 & matrix ) = 0;
			virtual void		set_projection ( const mat4 & matrix ) = 0;

			virtual void		set_clear_color ( const color & cr ) = 0;

			virtual void		clear () = 0;

			virtual void		begin_frame () = 0;
			virtual void		end_frame () = 0;

			virtual void		set_current_mesh ( imesh * mesh ) = 0;
			virtual imesh *		get_current_mesh () = 0;

			virtual void		set_current_texture ( itexture * texture ) = 0;
				
			virtual void		present () = 0;

			virtual void		destroy () = 0;
		};

	}
}

#endif