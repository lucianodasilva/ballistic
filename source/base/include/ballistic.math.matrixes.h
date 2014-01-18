#ifndef	_ballistic_math_matrixes_h_
#define _ballistic_math_matrixes_h_

#include "ballistic.config.h"
#include "ballistic.math.vectors.h"

namespace ballistic {
namespace math {

	template < class T >
	struct mat4_t {

		typedef T type;

		static const uint32_t count = 16;

		union {
			T data [count];

			struct {
				T m00, m01, m02, m03;
				T m04, m05, m06, m07;
				T m08, m09, m10, m11;
				T m12, m13, m14, m15;
			};
		};


		inline mat4_t ();

		inline mat4_t ( const mat4_t < T > & v );
		inline mat4_t ( T _m00, T _m01, T _m02, T _m03, T _m04, T _m05, T _m06, T _m07, T _m08, T _m09, T _m10, T _m11, T _m12, T _m13, T _m14, T _m15 );

		inline mat4_t & operator = ( const mat4_t < T > & v );

		inline mat4_t operator * ( const mat4_t < T > & v ) const;

		inline vec4_t < T > operator * ( const vec4_t < T > & v ) const;
		inline vec3_t < T > operator * ( const vec3_t < T > & v ) const;

		inline mat4_t transpose () const;

		// Create matrixes
		static mat4_t make_translation ( const vec3_t < T > & p );
		static mat4_t make_translation ( const vec4_t < T > & p );

		static mat4_t make_rotation_x ( T r );
		static mat4_t make_rotation_y ( T r );
		static mat4_t make_rotation_z ( T r );

		static mat4_t make_scale ( const vec3_t < T > & p );
		static mat4_t make_scale ( const vec4_t < T > & p );
	};

}
}

#include "ballistic.math.matrixes.inl"

typedef ballistic::math::mat4_t < real > mat4;

#endif