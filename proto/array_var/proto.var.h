#ifndef _proto_var_h_
#define _proto_var_h_

#include <inttypes.h>

namespace proto{

	struct var {

		typedef float real_t;
		typedef int32_t int_t;

		union {

			int_t		i_vector_16 [16];
			real_t		r_vector_16 [16];
			char		small_string [sizeof (real_t)* 16];

		};



	};

}

#endif