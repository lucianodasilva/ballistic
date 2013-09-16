#include "ballistic.graphics.opengl_material.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		opengl_material::opengl_material (uint8 run_id) :
			_run_id (run_id),
			_texture (nullptr),
			_effect (nullptr),
			_opaque (false)
		{}

		uint8 opengl_material::get_run_id () { return _run_id; }

		void opengl_material::set_effect (ieffect * effect) {
			_effect = dynamic_cast <opengl_effect *> (effect);

			if (!_effect) {
				debug_error ("GL material set effect cannot be converted to opengl_effect.");
				return;
			}

			_diffuse_constant = _effect->get_constant (id::graphics::effect::diffuse);
			_specular_constant = _effect->get_constant (id::graphics::effect::specular);
		}

		ieffect * opengl_material::get_effect () {
			return _effect;
		}

		void opengl_material::set_diffuse (const color & v) {
			_diffuse = v;
		}

		color opengl_material::get_diffuse () {
			return _diffuse;
		}

		void opengl_material::set_specular (const color & v) {
			_specular = v;
		}

		color opengl_material::get_specular () {
			return _specular;
		}

		void opengl_material::set_opaque (bool v) {
			_opaque = v;
		}

		bool opengl_material::get_opaque () {
			return _opaque;
		}

		void opengl_material::set_texture (itexture * v) {
			_texture = v;
		}

		itexture * opengl_material::get_texture () {
			return _texture;
		}

		void opengl_material::apply (idevice * device) {
			if (!_effect) {
				debug_error ("GL material has no bound effect");
				return;
			}

			// apply material
			_effect->set_constant (_diffuse_constant, _diffuse);
			_effect->set_constant (_specular_constant, _specular);
		}

	}
}