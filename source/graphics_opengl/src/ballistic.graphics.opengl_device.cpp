#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		opengl_device::opengl_device () {
			glewInit ();
		}
	
		imaterial * opengl_device::create_material ()
		{
			return nullptr;
		}
		
		imesh *	opengl_device::create_mesh ()
		{
			return nullptr;
		}
		
		itexture * opengl_device::create_texture (const point & size)
		{
			return nullptr;
		}
		
		imaterial * opengl_device::load_material ( const string & filename )
		{
			return nullptr;
		}
		
		imesh *	opengl_device::load_mesh ( const string & filename )
		{
			return nullptr;
		}
		
		itexture * opengl_device::load_texture ( const string & filename )
		{
			return nullptr;
		}
		
		void opengl_device::set_transform(const mat4 & matrix)
		{
			mat4 rev = matrix.transpose();
			glLoadMatrixf (&rev.data [0]);
		}

		void opengl_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void opengl_device::clear () {
			glClearColor (
				_clear_color.r,
				_clear_color.g,
				_clear_color.b,
				_clear_color.a
			);

			glClear (GL_COLOR_BUFFER_BIT);
		}
		
		void opengl_device::begin_frame ()
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		
		void opengl_device::end_frame ()
		{
			glFlush ();
		}
		
		void opengl_device::set_current_mesh ( imesh * mesh )
		{
		
		}
		
		void opengl_device::set_current_texture ( itexture * texture )
		{
		
		}
		
		void opengl_device::present ()
		{
		
		}
		
		void opengl_device::destroy ()
		{
		
		}
	
	}
}