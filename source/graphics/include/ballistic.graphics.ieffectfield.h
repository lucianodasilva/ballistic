#ifndef _ballistic_graphics_ieffectfield_h_
#define _ballistic_graphics_ieffectfield_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class ieffectfield {
		public:
			
			virtual id_t get_id () = 0;

			virtual void set_value (const var & v ) = 0;
			virtual var get_value () = 0;
			
			virtual void apply () = 0;
			
			virtual ieffectfield * clone () = 0;

		};

	}
}

#endif //!_ballistic_graphics_ieffectfield_h_
