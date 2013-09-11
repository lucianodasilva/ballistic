#ifndef _ballistic_vector_inl_
#define _ballistic_vector_inl_

#include <utility>

namespace ballistic {
namespace math {

	template < class T >
	const uint32 vec2_t < T >::count (2);

	template < class T >
	const vec2_t < T > vec2_t < T >::zero ( T(0), T (0) );

	template < class T >
	const vec2_t < T > vec2_t < T >::one ( T (1), T (1) );

	template < class T >
	vec2_t < T >::vec2_t  (T vx, T vy) : x (vx), y (vy) {}

	template < class T >
	vec2_t < T >::vec2_t () : x (T ()), y (T ()) {}

	template < class T >
	vec2_t < T >::vec2_t ( const vec2_t < T > & v ) : x (v.x), y (v.y) {}

	template < class T >
	vec2_t < T > & vec2_t < T >::operator = ( vec2_t < T > v ) {
		x = v.x;
		y = v.y;

		return *this;
	}

	template < class T >
	vec2_t < T > vec2_t < T >::operator + ( const vec2_t < T > & v ) const {
		return vec2_t ( x + v.x, y + v.y );
	}

	template < class T >
	vec2_t < T > vec2_t < T >::operator - ( const vec2_t < T > & v ) const {
		return vec2_t ( x - v.x, y - v.y);
	}

	template < class T >
	vec2_t < T > vec2_t < T >::operator * ( T v ) const {
		return vec2_t < T > ( x * v, y * v);
	}

	template < class T >
	vec2_t < T > vec2_t < T >::operator / ( T v ) const {
		return vec2_t ( x / v, y / v);
	}

	template < class T >
	vec2_t < T > & vec2_t < T >::operator += ( const vec2_t < T > & v ) {
		x += v.x;
		y += v.y;

		return *this;
	}

	template < class T >
	vec2_t < T > & vec2_t < T >::operator -= ( const vec2_t < T > & v ) {
		x -= v.x;
		y -= v.y;

		return *this;
	}

	template < class T >
	vec2_t < T > & vec2_t < T >::operator *= ( T v ) {
		x *= v;
		y *= v;

		return *this;
	}

	template < class T >
	vec2_t < T > & vec2_t < T >::operator /= ( T v ) {
		x /= v;
		y /= v;

		return *this;
	}

	template < class T >
	vec2_t < T >::operator T * () {
		return &data [0];
	}

	// ----------------------------------------------------------------------------

	template < class T >
	const uint32 vec3_t < T >::count (3);

	template < class T >
	const vec3_t < T > vec3_t < T >::zero ( T (0), T (0), T (0) );

	template < class T >
	const vec3_t < T > vec3_t < T >::one ( T (1), T (1), T (1) );

	template < class T >
	vec3_t < T >::vec3_t (T vx, T vy, T vz) : x (vx), y (vy), z(vz) {}

	template < class T >
	vec3_t < T >::vec3_t () : x (T ()), y (T ()), z (T ()) {}

	template < class T >
	vec3_t < T >::vec3_t ( const vec3_t < T > & v ) : x (v.x), y (v.y), z (v.z) {}

	template < class T >
	vec3_t < T > & vec3_t < T >::operator = ( vec3_t < T > v ) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	template < class T >
	vec3_t < T > vec3_t < T >::operator + ( const vec3_t < T > & v ) const {
		return vec3_t ( x + v.x, y + v.y, z + v.z );
	}

	template < class T >
	vec3_t < T > vec3_t < T >::operator - ( const vec3_t < T > & v ) const {
		return vec3_t ( x - v.x, y - v.y, z - v.z );
	}

	template < class T >
	vec3_t < T > vec3_t < T >::operator * ( T v ) const {
		return vec3_t ( x * v, y * v, z * v);
	}

	template < class T >
	vec3_t < T > vec3_t < T >::operator / ( T v ) const {
		return vec3_t ( x / v, y / v, z / v);
	}

	template < class T >
	vec3_t < T > & vec3_t < T >::operator += ( const vec3_t < T > & v ) {
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	template < class T >
	vec3_t < T > & vec3_t < T >::operator -= ( const vec3_t < T > & v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	template < class T >
	vec3_t < T > & vec3_t < T >::operator *= ( T v ) {
		x *= v;
		y *= v;
		z *= v;

		return *this;
	}

	template < class T >
	vec3_t < T > & vec3_t < T >::operator /= ( T v ) {
		x /= v;
		y /= v;
		z /= v;

		return *this;
	}

	template < class T >
	vec3_t < T >::operator T * () {
		return &data [0];
	}

	// ----------------------------------------------------------------------------

	template < class T >
	const uint32 vec4_t < T >::count (4);

	template < class T >
	const vec4_t < T > vec4_t < T >::zero ( T (0), T (0), T (0), T (0) );

	template < class T >
	const vec4_t < T > vec4_t < T >::one ( T (1), T (1), T (1), T (1) );

	template < class T >
	vec4_t < T >::vec4_t (T vx, T vy, T vz, T vw) : x (vx), y (vy), z(vz), w (vw) {}

	template < class T >
	vec4_t < T >::vec4_t () : x (T ()), y (T ()), z (T ()), w (T ()) {}

	template < class T >
	vec4_t < T >::vec4_t ( const vec4_t < T > & v ) : x (v.x), y (v.y), z (v.z), w (v.w) {}

	template < class T >
	vec4_t < T > & vec4_t < T >::operator = ( vec4_t < T > v ) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}

	template < class T >
	vec4_t < T > vec4_t < T >::operator + ( const vec4_t < T > & v ) const {
		return vec4_t ( x + v.x, y + v.y, z + v.z, w + v.w );
	}

	template < class T >
	vec4_t < T > vec4_t < T >::operator - ( const vec4_t < T > & v ) const {
		return vec4_t ( x - v.x, y - v.y, z - v.z, w - v.w );
	}

	template < class T >
	vec4_t < T > vec4_t < T >::operator * ( T v ) const {
		return vec4_t ( x * v, y * v, z * v, w * v);
	}

	template < class T >
	vec4_t < T > vec4_t < T >::operator / ( T v ) const {
		return vec4_t ( x / v, y / v, z / v, w / v);
	}

	template < class T >
	vec4_t < T >::operator T * () {
		return &data [0];
	}

	template < class T >
	vec4_t < T > & vec4_t < T >::operator += ( const vec4_t < T > & v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	template < class T >
	vec4_t < T > & vec4_t < T >::operator -= ( const vec4_t < T > & v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	template < class T >
	vec4_t < T > & vec4_t < T >::operator *= ( T v ) {
		x *= v;
		y *= v;
		z *= v;
		w *= v;

		return *this;
	}

	template < class T >
	vec4_t < T > & vec4_t < T >::operator /= ( T v ) {
		x /= v;
		y /= v;
		z /= v;
		w /= v;

		return *this;
	}

}
}

#endif