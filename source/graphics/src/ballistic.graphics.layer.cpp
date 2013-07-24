#include "ballistic.graphics.layer.h"

#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {

		ilayer::~ilayer () {}

		void layer::clear () {
			_items.clear ();
		}

		void layer::push_renderable (imesh * mesh, imaterial * material) {
			_items.resize (_items.size () + 1);
			renderable & rnd = _items.back ();

			rnd.mesh = mesh;
			rnd.material = material;
		}

		void layer::render (idevice * device) {
			for (renderable & rnd : _items) {
				
			}
		}

	}
}