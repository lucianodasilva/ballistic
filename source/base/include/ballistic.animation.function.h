#ifndef _ballistic_animation_function_h_
#define _ballistic_animation_function_h_

#include "ballistic.config.h"

namespace ballistic {
	namespace animation {

		class ifunction {
		public:
			virtual ~ifunction ();

			virtual real blend (real t, real v1, real v2, real c1 = real (), real c2 = real ()) = 0;
		};

		class linear : public ifunction {
		public:
			virtual real blend (real t, real v1, real v2, real c1 = real (), real c2 = real ());
		};

		class bezier : public ifunction {
		public:
			virtual real blend (real t, real v1, real v2, real c1 = real (), real c2 = real ());
		};

	}
}

#endif