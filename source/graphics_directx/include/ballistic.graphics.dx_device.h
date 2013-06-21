#ifndef ballistic_graphics_dx_device_h
#define ballistic_graphics_dx_device_h

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <d3d9.h>

namespace ballistic {
	namespace graphics {
		
		class dx_device : public idevice{
		private:

			color _clear_color;

			LPDIRECT3D9			_d3d;
			LPDIRECT3DDEVICE9	_d3d_device;

		public:
			
			dx_device (HWND hWnd);
			
			virtual imaterial * create_material ();
			virtual imesh *		create_mesh ();
			virtual itexture *	create_texture (const point & size);
			
			virtual imaterial * load_material ( const string & filename );
			virtual imesh *		load_mesh ( const string & filename );
			virtual itexture *	load_texture ( const string & filename );
			
			virtual void		set_transform ( const mat4 & matrix );
			
			virtual void		set_projection ( const mat4 & matrix );

			virtual void		set_clear_color ( const color & cr ) ;

			virtual void		clear ();

			virtual void		begin_frame ();
			virtual void		end_frame ();
			
			virtual void		set_current_mesh ( imesh * mesh );
			virtual void		set_current_texture ( itexture * texture );
			
			virtual void		present ();
			
			virtual void		destroy ();
		};
		
	}
}

#endif
