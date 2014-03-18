#include "ballistic.animation.function.h"

#include <cmath>

namespace ballistic {
	namespace animation {

		ifunction::~ifunction () {}

		real linear::blend (real t, real v1, real v2, real c1, real c2) {
			return v1 + ((v2 - v1) * t);
		}

		real bezier::blend (real t, real v1, real v2, real c1, real c2) {
			// TODO: optimize the crap out of this
			return
				std::pow (real (1) - t, real (2)) * v1 + real (3) *
				std::pow (real (1) - t, real (3)) * t * c1 + 3 * (real (1) - t) *
				std::pow (t, real (2)) * c2 +
				std::pow (t, real (3)) * v2;
		}

	}
}
