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
		class opengl_material;
		class opengl_mesh;
		
		class opengl_device : public idevice{
		private:

			color _clear_color;

			atomic <unsigned char> _effect_run_id;
			atomic <unsigned char> _material_run_id;
			atomic <unsigned char> _mesh_run_id;

			mat4	_view;

			opengl_effect *		_effect;
			opengl_material *	_material;
			opengl_mesh *		_mesh;

			// constants
			opengl_constant		_gl_const_world;
			opengl_constant		_gl_const_view;

		public:
			
			opengl_device ();
			
			virtual ieffect *	create_effect ();
			virtual imaterial * create_material ();
			virtual imesh *		create_mesh ();
			virtual itexture *	create_texture (const point & size);

			virtual void		activate (ieffect * effect);
			virtual void		activate (imaterial * material);
			virtual void		activate (imesh * mesh);
			
			virtual void		set_clear_color ( const color & cr );

			virtual void 		set_view (const mat4 & view);
			virtual const mat4 & get_view ();

			virtual void		clear ();

			virtual void		begin_frame ();
			virtual void		end_frame ();

			virtual void		present ();
			
			virtual void		destroy ();

			virtual void		draw_active_mesh (const mat4 transform);
		};
		
	}
}

#endif
