#include "ballistic.graphics.dx_device.h"

#include <d3d9.h>

#include "ballistic.graphics.dx_mesh.h"

namespace ballistic {
	namespace graphics {
		
		dx_device::dx_device () {
			
		}
	
		imaterial * dx_device::create_material ()
		{
			return nullptr;
		}
		
		imesh *	dx_device::create_mesh ()
		{
			return new opengl_mesh ();
		}
		
		itexture * dx_device::create_texture (const point & size)
		{
			return nullptr;
		}
		
		imaterial * dx_device::load_material ( const string & filename )
		{
			return nullptr;
		}
		
		imesh *	dx_device::load_mesh ( const string & filename )
		{
			return nullptr;
		}
		
		itexture * dx_device::load_texture ( const string & filename )
		{
			return nullptr;
		}
		
		void dx_device::set_transform(const mat4 & matrix)
		{
			mat4 rev = matrix.transpose();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMultMatrixf (&rev.data [0]);
		}
		
		void dx_device::set_projection ( const mat4 & matrix ) {
			mat4 rev = matrix.transpose ();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMultMatrixf (&rev.data [0]);
		}

		void dx_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void dx_device::clear () {
			glClearColor (
				_clear_color.r,
				_clear_color.g,
				_clear_color.b,
				_clear_color.a
			);

			glClear (GL_COLOR_BUFFER_BIT);
		}
		
		void dx_device::begin_frame ()
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		
		void dx_device::end_frame ()
		{
			//glFlush ();
		}
		
		void dx_device::set_current_mesh ( imesh * mesh )
		{
		
		}
		
		void dx_device::set_current_texture ( itexture * texture )
		{
		
		}
		
		void dx_device::present ()
		{
		
		}
		
		void dx_device::destroy ()
		{
		
		}
	
	}
}