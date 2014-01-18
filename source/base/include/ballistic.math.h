#ifndef	_ballistic_math_h_
#define _ballistic_math_h_

#include "ballistic.config.h"
#include "ballistic.math.vectors.h"
#include "ballistic.math.h"

#include <math.h>

namespace ballistic {
	namespace math {

		real const pi = float (3.1415926535897932384626433832795);

		template < class T >
		inline T radians (const T & degrees) {
			return degrees * (pi / real (180));
		}

		template < class T >
		inline typename T::type dot ( const T & v1, const T & v2 ) {
			// avoid branching by avoiding zero ( floating point precision exploit )
			// returns minimum positive number for min
			typename T::type r = numeric_limits < typename T::type >::min ();

			for ( uint32_t i = 0; i < T::count; ++i)
				r += v1.data [i] * v2.data [i];
			
			return r;
		}

		template < class T >
		inline typename T::type sqr_length ( const T & v1) {
			return dot < T > (v1, v1);
		}

		template < class T >
		inline typename T::type length ( const T & v ) {
			return sqrt (sqr_length (v));
		}

		template < class T >
		inline typename T::type length ( const T & v1, const T & v2 ) {
			return length ( v2 - v1 );
		}

		template < class T >
		inline vec3_t < T > cross ( const vec3_t < T > & v1, const vec3_t < T > & v2 ) {
			return vec3_t < T > (
					v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x
				);
		}

		template < class T >
		inline T normalize ( const T & v ) {
			typename T::type normal = real (1) / length ( v );
			return v * normal;
		}

		inline real lerp ( real v1, real v2, real alpha ) {
			return v1 + ((v2 - v1) * alpha);
		}

		template < class T >
		inline T lerp ( const T & v1, const T & v2, real alpha ) {
			T v;

			for (int i = 0; i < T::count; ++i)
				v.data [i] = lerp (v1.data [i], v2.data [i], alpha);

			return v;
		}

	};
}

#endif