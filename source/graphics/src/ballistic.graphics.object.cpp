#include "ballistic.graphics.object.h"

namespace ballistic {
	namespace graphics {

		object::object () : _mesh (nullptr), _material (nullptr) {}

		void object::set_mesh (imesh * mesh) {
			_mesh = mesh;
		}

		imesh * object::get_mesh () {
			return _mesh;
		}

		void object::set_material (imaterial * material) {
			_material = material;
		}

		imaterial * object::get_material () {
			return _material;
		}

		void object::set_transform (mat4 transform) {
			_transform = transform;
		}

		const mat4 & object::get_transform () {
			return _transform;
		}

	}
}