#include "ballistic.graphics.opengl_material.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		opengl_material::opengl_material (const id_t & id) :
			imaterial (id),
			_opaque (false),
			_texture (nullptr),
			_effect (nullptr)
		{}

		void opengl_material::effect (ieffect * effect) {
			_effect = dynamic_cast <opengl_effect *> (effect);

			if (!_effect) {
				debug_error ("GL material set effect cannot be converted to opengl_effect.");
				return;
			}

			properties.bind (effect);

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

			properties.apply ();

			// apply material
			_effect->constant (_diffuse_constant, _diffuse);
			_effect->constant (_specular_constant, _specular);
		}

	}
}