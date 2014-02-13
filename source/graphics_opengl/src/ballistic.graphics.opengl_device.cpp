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
			_material_run_id (0),
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
				debug_print ("OpenGL version: " << gl_str_version);
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
				glEnable (GL_POLYGON_SMOOTH);

			}

			// debug initialize
			debug_run (
				opengl_debug::initialize ();
			);
			
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
			//_gl_const_model = _effect->get_constant (id::graphics::effect::t_model);
			_gl_const_view = _effect->get_constant (id::graphics::effect::t_view);
			_gl_const_proj = _effect->get_constant (id::graphics::effect::t_proj);
			_gl_const_normal = _effect->get_constant (id::graphics::effect::t_normal);
			
			_gl_const_diffuse = _effect->get_constant (id::graphics::effect::diffuse);
			_gl_const_specular = _effect->get_constant (id::graphics::effect::specular);

			// set least changing constants
			// TODO: replace by uniform block
			_effect->set_constant (_gl_const_view, _view);
			//_effect->set_constant (_gl_const_model, _model);
			_effect->set_constant (_gl_const_proj, _proj);
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
			if (_effect)
				_effect->set_constant (_gl_const_view, _view);
		}

		const mat4 & opengl_device::get_view () const {
			return _view;
		}

		void opengl_device::set_model (const mat4 & model) {
			_model = model;
			if (_effect)
				_effect->set_constant (_gl_const_model, _model);
		}

		const mat4 & opengl_device::get_model () const {
			return _model;
		}

		void opengl_device::set_proj (const mat4 & proj) {
			_proj = proj;

			if (_effect)
				_effect->set_constant (_gl_const_proj, _proj);
		}

		const mat4 & opengl_device::get_proj () const {
			return _proj;
		}
		
		void opengl_device::set_normal (const mat4 & norm) {
			_normal = norm;
			
			if (_effect)
				_effect->set_constant (_gl_const_normal, _normal);
		}
		
		const mat4 & opengl_device::get_normal () const {
			return _normal;
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