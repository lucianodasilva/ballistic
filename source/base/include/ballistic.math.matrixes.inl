
#include <cmath>

namespace ballistic {
namespace math {

	template < class T >
	mat4_t < T >::mat4_t () :
		m00 (T (1)), m01 (T (0)), m02 (T (0)), m03 (T (0)),
		m04 (T (0)), m05 (T (1)), m06 (T (0)), m07 (T (0)),
		m08 (T (0)), m09 (T (0)), m10 (T (1)), m11 (T (0)),
		m12 (T (0)), m13 (T (0)), m14 (T (0)), m15 (T (1))
	{}

	template < class T >
	mat4_t < T >::mat4_t ( T _m00, T _m01, T _m02, T _m03, T _m04, T _m05, T _m06, T _m07, T _m08, T _m09, T _m10, T _m11, T _m12, T _m13, T _m14, T _m15 )
		:
		m00 (_m00), m01 (_m01), m02 (_m02), m03 (_m03),
		m04 (_m04), m05 (_m05), m06 (_m06), m07 (_m07),
		m08 (_m08), m09 (_m09), m10 (_m10), m11 (_m11),
		m12 (_m12), m13 (_m13), m14 (_m14), m15 (_m15)
	{}

	template < class T >
	mat4_t < T > & mat4_t < T >::operator = ( const mat4_t & v ) {
		for ( int i = 0; i < count; ++i )
			data [i] = v.data [i];

		return *this;
	}

	template < class T >
	mat4_t < T > mat4_t < T >::operator * ( const mat4_t & v ) const {
		return mat4_t (
			data[ 0]*v.data[ 0] +
			data[ 1]*v.data[ 4] +
			data[ 2]*v.data[ 8] +
			data[ 3]*v.data[12],

			data[ 0]*v.data[ 1] +
			data[ 1]*v.data[ 5] +
			data[ 2]*v.data[ 9] +
			data[ 3]*v.data[13],

			data[ 0]*v.data[ 2] +
			data[ 1]*v.data[ 6] +
			data[ 2]*v.data[10] +
			data[ 3]*v.data[14],

			data[ 0]*v.data[ 3] +
			data[ 1]*v.data[ 7] +
			data[ 2]*v.data[11] +
			data[ 3]*v.data[15],

			data[ 4]*v.data[ 0] +
			data[ 5]*v.data[ 4] +
			data[ 6]*v.data[ 8] +
			data[ 7]*v.data[12],

			data[ 4]*v.data[ 1] +
			data[ 5]*v.data[ 5] +
			data[ 6]*v.data[ 9] +
			data[ 7]*v.data[13],

			data[ 4]*v.data[ 2] +
			data[ 5]*v.data[ 6] +
			data[ 6]*v.data[10] +
			data[ 7]*v.data[14],

			data[ 4]*v.data[ 3] +
			data[ 5]*v.data[ 7] +
			data[ 6]*v.data[11] +
			data[ 7]*v.data[15],

			data[ 8]*v.data[ 0] +
			data[ 9]*v.data[ 4] +
			data[10]*v.data[ 8] +
			data[11]*v.data[12],

			data[ 8]*v.data[ 1] +
			data[ 9]*v.data[ 5] +
			data[10]*v.data[ 9] +
			data[11]*v.data[13],

			data[ 8]*v.data[ 2] +
			data[ 9]*v.data[ 6] +
			data[10]*v.data[10] +
			data[11]*v.data[14],

			data[ 8]*v.data[ 3] +
			data[ 9]*v.data[ 7] +
			data[10]*v.data[11] +
			data[11]*v.data[15],

			data[12]*v.data[ 0] +
			data[13]*v.data[ 4] +
			data[14]*v.data[ 8] +
			data[15]*v.data[12],

			data[12]*v.data[ 1] +
			data[13]*v.data[ 5] +
			data[14]*v.data[ 9] +
			data[15]*v.data[13],

			data[12]*v.data[ 2] +
			data[13]*v.data[ 6] +
			data[14]*v.data[10] +
			data[15]*v.data[14],

			data[12]*v.data[ 3] +
			data[13]*v.data[ 7] +
			data[14]*v.data[11] +
			data[15]*v.data[15]
		);
	}

	template < class T >
	vec4_t < T > mat4_t < T >::operator * ( const vec4_t < T > & v ) const {
		return vec4_t < T > (
			v.x * data [0] + v.y * data [4] + v.z * data[8] + v.w * data [12],
			v.x * data [1] + v.y * data [5] + v.z * data[9] + v.w * data [13],
			v.x * data [2] + v.y * data [6] + v.z * data[10] + v.w * data [14],
			v.x * data [3] + v.y * data [7] + v.z * data[11] + v.w * data [15]
		);
	}

	template < class T >
	vec3_t < T > mat4_t < T >::operator * ( const vec3_t < T > & v ) const {
		return vec3_t < T > (
			v.x * data [0] + v.y * data [4] + v.z * data[8] + T (1) * data [12],
			v.x * data [1] + v.y * data [5] + v.z * data[9] + T (1) * data [13],
			v.x * data [2] + v.y * data [6] + v.z * data[10] + T (1)  * data [14]
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::transpose () const {
		return mat4_t (
			data[ 0],
			data[ 4],
			data[ 8],
			data[12],
			data[ 1],
			data[ 5],
			data[ 9],
			data[13],
			data[ 2],
			data[ 6],
			data[10],
			data[14],
			data[ 3],
			data[ 7],
			data[11],
			data[15]
		);
	}

	// Create matrix
	template < class T >
	mat4_t < T > mat4_t < T >::make_translation ( const vec3_t < T > & p ) {
		return mat4_t (
			T (1), T (0), T (0), T (0),
			T (0), T (1), T (0), T (0),
			T (0), T (0), T (1), T (0),
			p.x,	  p.y,		p.z,	  T (1)
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_translation ( const vec4_t < T > & p ) {
		return mat4_t (
			T (1), T (0), T (0), T (0),
			T (0), T (1), T (0), T (0),
			T (0), T (0), T (1), T (0),
			p.x,	  p.y,		p.z,	  p.w
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_rotation_x ( T r ) {
		T 
			r_sin = sin (r),
			r_cos = cos (r);

		return mat4_t < T > (
			T (1), T (0), T (0), T (0),
			T (0), r_cos, r_sin, T (0),
			T (0), -r_sin, r_cos, T (0),
			T (0), T (0),	T (0), T (1)
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_rotation_y ( T r ) {
		T 
			r_sin = sin (r),
			r_cos = cos (r);

		return mat4_t < T > (
			r_cos, T (0), -r_sin, T (0),
			T (0), T (1), T (0), T (0),
			r_sin, T (0), r_cos, T (0),
			T (0), T (0),	T (0), T (1)
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_rotation_z ( T r ) {
		T 
			r_sin = sin (r),
			r_cos = cos (r);

		return mat4_t < T > (
			r_cos, r_sin, T (0), T (0),
			-r_sin, r_cos, T (0), T (0),
			T (0), T (0), T (1), T (0),
			T (0), T (0),	T (0), T (1)
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_scale ( const vec3_t < T > & p ) {
		return mat4_t < T >(
			p.x, T (0), T (0), T (0),
			T (0), p.y, T (0), T (0),
			T (0), T (0), p.z, T (0),
			T (0), T (0), T (0), T (1)
		);
	}

	template < class T >
	mat4_t < T > mat4_t < T >::make_scale ( const vec4_t < T > & p ) {
		return mat4_t < T > (
			p.x, T (0), T (0), T (0),
			T (0), p.y, T (0), T (0),
			T (0), T (0), p.z, T (0),
			T (0), T (0), T (0), p.w
		);
	}

}
}