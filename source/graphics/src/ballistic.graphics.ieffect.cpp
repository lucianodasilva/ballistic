#include "ballistic.graphics.ieffect.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		bool iconstant::is_null () { return false; }
		iconstant::~iconstant () {}

		null_constant null_constant::instance;

		void null_constant::set_value (uint32_t v) {}
		void null_constant::set_value (int32_t v) {}
		void null_constant::set_value (real v) {}
		void null_constant::set_value (const vec2 & v) {}
		void null_constant::set_value (const vec3 & v) {}
		void null_constant::set_value (const vec4 & v) {}
		void null_constant::set_value (const mat4 & v) {}

		bool null_constant::is_null () { return true; }

	}
}
