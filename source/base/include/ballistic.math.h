#ifndef	_ballistic_math_h_
#define _ballistic_math_h_

#include "ballistic.vectors.h"

#include <math.h>

namespace ballistic {
	namespace math {

		template < class v_t >
		inline real dot ( const v_t & v1, const v_t & v2 ) {
			real r = real ();

			for ( uint32 i = 0; i < v_t::data_length; ++i) 
				r += v1.data [i] * v2.data [i];
			
			return r;
		}

		template < class v_t >
		inline real sqr_length ( const v_t & v1) {
			return dot < v_t > (v1, v1);
		}

		template < class v_t >
		inline real length ( const v_t & v ) {
			return sqrt (sqr_length (v));
		}

		template < class v_t >
		inline real length ( const v_t & v1, const v_t & v2 ) {
			return length ( v2 - v1 );
		}

		inline vec3 cross ( const vec3 & v1, const vec3 & v2 ) {
			return vec3 (
					v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x
				);
		}

		template < class v_t >
		inline v_t normalize ( const v_t & v ) {
			real normal = 1.0 / length ( v );
			return v * normal;
		}

		inline real lerp ( real v1, real v2, real alpha ) {
			return v2 - v1 * alpha;
		}

		template < class v_t >
		inline v_t lerp ( const v_t & v1, const v_t & v2, real alpha ) {
			v_t v;

			for (int i = 0; i < v_t::data_length; ++i)
				v.data [i] = lerp (v1.data [i], v2.data [i], alpha);

			return v;
		}

	};
}

#endif