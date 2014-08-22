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

			_diffuse_constant = _effect->constant (id::graphics::effect::diffuse);
		}

		ieffect * opengl_material::effect () const {
			return _effect;
		}

		void opengl_material::diffuse (const color & v) {
			_diffuse = v;
		}

		color opengl_material::diffuse () const {
			return _diffuse;
		}


		void opengl_material::opaque (bool v) {
			_opaque = v;
		}

		bool opengl_material::opaque () const {
			return _opaque;
		}

		void opengl_material::texture (itexture * v) {
			_texture = v;
		}

		itexture * opengl_material::texture () const {
			return _texture;
		}

		void opengl_material::apply (idevice * device) {
			if (!_effect) {
				debug_error ("GL material has no bound effect");
				return;
			}

			// apply material
			if (_diffuse_constant)
				_diffuse_constant->set_value(_diffuse);
		}

	}
}