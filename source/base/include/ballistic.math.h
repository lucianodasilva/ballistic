#ifndef	_ballistic_math_h_
#define _ballistic_math_h_

#include "ballistic.config.h"
#include "ballistic.math.vectors.h"

#include <cmath>

namespace ballistic {
	namespace math {

		real const pi = float (3.1415926535897932384626433832795);

		template < class T >
		inline T radians (const T & degrees) {
			return degrees * (pi / real (180));
		}

		template < class value_t, class data_t >
		inline value_t dot ( const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2 ) {
			// avoid branching by avoiding zero ( floating point precision exploit )
			// returns minimum positive number for min
			value_t r = numeric_limits < value_t >::min ();

			for ( uint32_t i = 0; i < data_t::size; ++i)
				r += v1.data [i] * v2.data [i];
			
			return r;
		}

		template < class value_t, class data_t >
		inline value_t sqr_length ( const vecn_t < value_t, data_t > & v ) {
			return dot < value_t, data_t > (v, v);
		}

		template < class value_t, class data_t >
		inline value_t length (const vecn_t < value_t, data_t > & v) {
			return std::sqrt (sqr_length < value_t, data_t > (v));
		}

		template < class value_t, class data_t >
		inline value_t length (const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2) {
			return length < value_t, data_t >  ( v2 - v1 );
		}

		template < class value_t >
		inline vec3_t < value_t > cross (const vec3_t < value_t > & v1, const vec3_t < value_t > & v2) {
			return {
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x
			};
		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > normalize ( const vecn_t < value_t, data_t > & v ) {
			value_t norm = value_t (1) / length < value_t, data_t > ( v );
			return v * norm;
		}

		inline real lerp ( real v1, real v2, real alpha ) {
			return v1 + ((v2 - v1) * alpha);
		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > lerp (const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2, real alpha) {
			vecn_t < value_t, data_t > v;

			for (int i = 0; i < data_t::size; ++i)
				v.data [i] = lerp (v1.data [i], v2.data [i], alpha);

			return v;
		}

	};
}

#endif