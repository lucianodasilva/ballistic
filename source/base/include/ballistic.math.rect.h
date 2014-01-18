#ifndef	_ballistic_math_rect_h_
#define _ballistic_math_rect_h_

#include "ballistic.math.vectors.h"

namespace ballistic {
	namespace math {

		template < class T >
		struct rect_t {

			union {
				struct { T x, y, width, height; };
				struct { vec2_t < T > position, size; };
			};

			inline rect_t ();
			inline rect_t ( T x, T y, T width, T height );
			inline rect_t ( vec2_t < T > position, vec2_t < T > size );

			inline rect_t ( const rect_t < T > & v );
			inline rect_t < T > & operator = ( const rect_t < T > & v );

		};

	}
}

#include "ballistic.math.rect.inl"

typedef ballistic::math::rect_t < int32_t > rect;

#endif