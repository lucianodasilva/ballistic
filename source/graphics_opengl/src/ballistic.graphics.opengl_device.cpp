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
			_material_run_id (0),
			_effect (nullptr),
			_material (nullptr),
			_mesh (nullptr)
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

		void opengl_device::activate (ieffect * effect) {
			if (!effect) {
				debug_error ("[opengl_device::activate] Cannot set uninstantiated effect.");
				return;
			}

			_effect = reinterpret_cast <opengl_effect *> (effect);
			_effect->apply (this);

			// get constants
			_gl_const_world = _effect->get_constant (id::effect_t_world);
			_gl_const_view = _effect->get_constant (id::effect_t_view);

			// set least changing constants
			_effect->set_constant (_gl_const_view, _view);
		}

		void opengl_device::activate (imaterial * material) {
			_material = reinterpret_cast <opengl_material *>(material);
			_material->apply (this);
		}

		void opengl_device::activate (imesh * mesh) {
			_mesh = reinterpret_cast <opengl_mesh *>(mesh);
			_mesh->apply (this);
		}

		void opengl_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void opengl_device::set_view (const mat4 & view) {
			_view = view;
		}

		const mat4 & opengl_device::get_view () {
			return _view;
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

		void opengl_device::draw_active_mesh (const mat4 transform) {
			if (!_material) {
				debug_error ("draw_active_mesh: No active instance of material set.");
				return;
			}

			if (!_effect) {
				debug_error ("render_mesh: No active instance of effect set.");
				return;
			}

			if (!_mesh) {
				debug_error ("render_mesh: No active instance of mesh set.");
				return;
			}

			_effect->set_constant (_gl_const_world, transform);

			_mesh->render ();
		}

	
	}
}