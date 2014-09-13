#ifndef	_ballistic_math_rect_h_
#define _ballistic_math_rect_h_

#include "ballistic.math.vectors.h"

namespace ballistic {
	namespace math {

		template < class T >
		struct rect_t {

			union {
				struct { T x, y, width, height; };
				struct { vectors::vec2_t < T > position, size; };
			};

			inline rect_t ();
			inline rect_t ( T x, T y, T width, T height );
			inline rect_t ( vectors::vec2_t < T > position, vectors::vec2_t < T > size );

			inline rect_t ( const rect_t < T > & v );
			inline rect_t < T > & operator = ( const rect_t < T > & v );

		};

		template < class T >
		rect_t < T >::rect_t ()
			: x (T ()), y (T ()), width (T ()), height (T ()) {}

		template < class T >
		rect_t < T >::rect_t (T x, T y, T width, T height)
			: x (x), y (y), width (width), height (height) {}

		template < class T >
		rect_t < T >::rect_t (vectors::vec2_t < T > position, vectors::vec2_t < T > size)
			: position (position), size (size) {}

		template < class T >
		rect_t < T >::rect_t (const rect_t < T > & v)
			: position (v.position), size (v.size) {}

		template < class T >
		rect_t < T > & rect_t < T >::operator = (const rect_t < T > & v) {
			position = v.position;
			size = v.size;

			return *this;
		}

	}
}


typedef ballistic::math::rect_t < int32_t > rect;

#endif