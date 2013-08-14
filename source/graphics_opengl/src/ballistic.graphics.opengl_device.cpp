#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>
#include "ballistic.graphics.opengl_debug.h"
#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_material.h"
#include "ballistic.graphics.opengl_mesh.h"

namespace ballistic {
	namespace graphics {
		
		opengl_device::opengl_device ()
			:
			_effect_run_id (0),
			_mesh_run_id (0),
			_material_run_id (0)
		{

			glewExperimental = true;
			GLenum init_error = glewInit();
			if (init_error != GLEW_OK) {
				debug_error ("glew initialization error: " << glewGetErrorString(init_error));
			}
			
			glGetError (); // reset errors
			
			string gl_str_version = (const char *) glGetString (GL_VERSION);
			debug_print ("OpenGL version: " << gl_str_version);

			// debug initialize
			opengl_debug::initialize ();
			
		}

		ieffect * opengl_device::create_effect () {
			return new opengl_effect (++_effect_run_id);
		}

		imaterial * opengl_device::create_material () {
			return new opengl_material (++_material_run_id);
		}
		
		imesh *	opengl_device::create_mesh ()
		{
			return new opengl_mesh (++_mesh_run_id);
		}
		
		itexture * opengl_device::create_texture (const point & size)
		{
			return nullptr;
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
		
		}
		
		void opengl_device::present ()
		{
		
		}
		
		void opengl_device::destroy ()
		{
		
		}
	
	}
}