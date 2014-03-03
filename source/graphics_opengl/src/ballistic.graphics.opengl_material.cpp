#include "ballistic.graphics.opengl_material.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		opengl_material::opengl_material (id_t id, uint8_t run_id) :
			iresource (id),
			imaterial (*this),
			_opaque (false),
			_texture (nullptr),
			_effect (nullptr),
			_run_id (run_id)
		{}

		uint8_t opengl_material::run_id () { return _run_id; }

		void opengl_material::effect (ieffect * effect) {
			_effect = dynamic_cast <opengl_effect *> (effect);

			if (!_effect) {
				debug_error ("GL material set effect cannot be converted to opengl_effect.");
				return;
			}

			_diffuse_constant = _effect->constant (id::graphics::effect::diffuse);
			_specular_constant = _effect->constant (id::graphics::effect::specular);
		}

		ieffect * opengl_material::effect () {
			return _effect;
		}

		void opengl_material::diffuse (const color & v) {
			_diffuse = v;
		}

		color opengl_material::diffuse () {
			return _diffuse;
		}

		void opengl_material::specular (const color & v) {
			_specular = v;
		}

		color opengl_material::specular () {
			return _specular;
		}

		void opengl_material::opaque (bool v) {
			_opaque = v;
		}

		bool opengl_material::opaque () {
			return _opaque;
		}

		void opengl_material::texture (itexture * v) {
			_texture = v;
		}

		itexture * opengl_material::texture () {
			return _texture;
		}

		void opengl_material::apply (idevice * device) {
			if (!_effect) {
				debug_error ("GL material has no bound effect");
				return;
			}

			// apply material
			_effect->constant (_diffuse_constant, _diffuse);
			_effect->constant (_specular_constant, _specular);
		}

	}
}