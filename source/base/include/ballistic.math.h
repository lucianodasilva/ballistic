#ifndef	_ballistic_math_h_
#define _ballistic_math_h_

#include "ballistic.vectors.h"

#include <math.h>

namespace ballistic {
	namespace math {

		inline real sqr_length ( const vec2 & v ) {
			return v.x * v.x + v.y * v.y;
		}

		inline real sqr_length ( const vec3 & v ) {
			return v.x * v.x + v.y * v.y + v.z * v.z;
		}

		inline real sqr_length ( const vec4 & v ) {
			return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
		}

		template < class v_t >
		inline real length ( const v_t & v ) {
			return sqrt (sqr_length (v));
		}

		inline real length ( const vec2 & v1, const vec2 & v2 ) {
			return length ( v2 - v1 );
		}

		inline real dot ( const vec2 & v1, const vec2 & v2 ) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		inline real dot ( const vec3 & v1, const vec3 & v2 ) {
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		inline real dot ( const vec4 & v1, const vec4 & v2 ) {
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
		}

		inline vec3 cross ( const vec3 & v1, const vec3 & v2 ) {
			return vec3 (
					v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x
				);
		}

		template < class v_t >
		inline vec2 normalize ( const v_t & v ) {
			real normal = 1.0 / length ( v );
			return v * normal;
		}

	};
}

#endif