#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>
#include "ballistic.graphics.opengl_debug.h"
#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_material.h"
#include "ballistic.graphics.opengl_mesh.h"
#include "ballistic.graphics.opengl_texture.h"

namespace ballistic {
	namespace graphics {
		
		opengl_device::opengl_device ()
			:
			_alpha_blend (false),
			_effect_run_id (0),
			_mesh_run_id (0),
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
			
			debug_run ({
				string gl_str_version = (const char *)glGetString (GL_VERSION);
				debug_print ("openGL version: " << gl_str_version);
			});

			{
				gl_eval_scope ("enable gl flags");

				// enable depth testing
				glEnable (GL_DEPTH_TEST);

				// enable backface culling
				glCullFace (GL_BACK);
				glEnable (GL_CULL_FACE);

				// enable anti-aliasing
				//glEnable (GL_BLEND);
				//glEnable (GL_POLYGON_SMOOTH);

			}

			// debug initialize
			debug_run (
				opengl_debug::initialize ();
			);
			
		}

		ieffect * opengl_device::create_effect (const id_t & id) {
			return new opengl_effect (id, ++_effect_run_id);
		}

		imaterial * opengl_device::create_material (const id_t & id) {
			return new opengl_material(id);
		}
		
		imesh *	opengl_device::create_mesh (const id_t & id)
		{
			return new opengl_mesh (id, ++_mesh_run_id);
		}
		
		itexture * opengl_device::create_texture (const id_t & id)
		{
			return new opengl_texture (id, ++_texture_run_id);
		}

		void opengl_device::activate (ieffect * effect) {
			if (!effect) {
				debug_error ("cannot set uninstantiated effect.");
				return;
			}

			_effect = reinterpret_cast <opengl_effect *> (effect);
			_effect->apply (this);

			// get constants
			_gl_const_model = _effect->constant (id::graphics::effect::t_model);
			_gl_const_view = _effect->constant (id::graphics::effect::t_view);
			_gl_const_proj = _effect->constant (id::graphics::effect::t_proj);
			_gl_const_mvp = _effect->constant (id::graphics::effect::t_mvp);
			_gl_const_normal = _effect->constant (id::graphics::effect::t_normal);
			
			_gl_const_diffuse = _effect->constant (id::graphics::effect::diffuse);
		}

		void opengl_device::activate (imaterial * material) {
			_material = reinterpret_cast <opengl_material *>(material);
			_material->apply (this);
		}

		void opengl_device::activate (imesh * mesh) {
			_mesh = reinterpret_cast <opengl_mesh *>(mesh);
			_mesh->apply (this);
		}

		void opengl_device::activate (itexture * texture) {
			_texture = reinterpret_cast <opengl_texture *> (texture);
			_texture->apply (this);
		}

		bool opengl_device::alpha_blend () {
			return _alpha_blend;
		}

		void opengl_device::alpha_blend (const bool & v) {
			if (v) {
				_alpha_blend = true;
				glEnable (GL_BLEND);
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			} else {
				_alpha_blend = false;
				glDisable (GL_BLEND);
			}
		}

		void opengl_device::clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		color opengl_device::clear_color() const {
			return _clear_color;
		}

		void opengl_device::set_view (const mat4 & view) {
			if (_gl_const_view)
				_gl_const_view->set_value(view);
		}

		void opengl_device::set_model (const mat4 & model) {
			if (_gl_const_model)
				_gl_const_model->set_value(model);
		}

		void opengl_device::set_proj (const mat4 & proj) {
			if (_gl_const_proj)
				_gl_const_proj->set_value(proj);
		}

		void opengl_device::set_mvp(const mat4 & mvp) {
			if (_gl_const_mvp)
				_gl_const_mvp->set_value(mvp);
		}
		
		void opengl_device::set_normal (const mat4 & norm) {
			if (_gl_const_normal)
				_gl_const_normal->set_value(norm);
		}

		void opengl_device::clear () {
			glClearColor (
				_clear_color.r,
				_clear_color.g,
				_clear_color.b,
				_clear_color.a
			);

			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}

		void opengl_device::begin_frame ()
		{
			glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );			
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

		void opengl_device::draw_active_mesh () {
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
			_mesh->render ();
		}

	
	}
}