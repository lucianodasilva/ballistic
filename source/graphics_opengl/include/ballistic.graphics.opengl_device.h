#ifndef ballistic_graphics_opengl_device_h
#define ballistic_graphics_opengl_device_h

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <atomic>

using namespace std;

namespace ballistic {
	namespace graphics {
		
		class opengl_device : public idevice{
		private:

			color _clear_color;

			atomic <unsigned char> _effect_run_id;
			atomic <unsigned char> _material_run_id;
			atomic <unsigned char> _mesh_run_id;

		public:
			
			opengl_device ();
			
			virtual ieffect *	create_effect ();
			virtual imaterial * create_material ();
			virtual imesh *		create_mesh ();
			virtual itexture *	create_texture (const point & size);
			
			virtual void		set_clear_color ( const color & cr ) ;

			virtual void		clear ();

			virtual void		begin_frame ();
			virtual void		end_frame ();

			virtual void		present ();
			
			virtual void		destroy ();
		};
		
	}
}

#endif
