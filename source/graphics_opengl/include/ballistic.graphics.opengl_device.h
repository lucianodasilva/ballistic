#ifndef ballistic_graphics_opengl_device_h
#define ballistic_graphics_opengl_device_h

#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <atomic>

#include "ballistic.graphics.opengl_effect.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class opengl_effect;
		class opengl_mesh;
		class opengl_texture;
		
		class opengl_device : public idevice {
		private:

			bool _alpha_blend;

			color _clear_color;

			atomic <unsigned char> _effect_run_id;
			atomic <unsigned char> _mesh_run_id;
			atomic <unsigned char> _texture_run_id;

			opengl_effect *		_effect;
			opengl_mesh *		_mesh;
			opengl_texture *	_texture;

		public:
			
			opengl_device ();
			
			virtual ieffect *	create_effect (const id_t & id);
			virtual imesh *		create_mesh (const id_t & id);
			virtual itexture *	create_texture (const id_t & id);

			virtual void		activate (ieffect * effect);
			virtual void		activate (imesh * mesh);
			virtual void		activate (itexture * texture);

			virtual bool		alpha_blend ();
			virtual void		alpha_blend (const bool & v);
			
			virtual void		clear_color ( const color & cr );
			virtual color		clear_color() const;

			virtual void		clear ();

			virtual void		begin_frame ();
			virtual void		end_frame ();

			virtual void		present ();
			
			virtual void		destroy ();

			virtual void		draw_active_mesh ();
		};
		
	}
}

#endif
