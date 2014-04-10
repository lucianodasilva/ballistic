#ifndef	_ballistic_math_quat_h_
#define _ballistic_math_quat_h_

#include "ballistic.config.h"
#include "ballistic.math.h"
#include "ballistic.math.vectors.h"

namespace ballistic {
namespace math {

	template < class T >
	struct quat_t {
		
		typedef T type;
		
		static const uint32_t count;
		
		union {
			T data [4];
			struct { vec3_t < T > v; T w; };
		};
		
		// constructor
		inline quat_t ();
		inline quat_t (T vx, T vy, T vz, T vw);
		inline quat_t (const vec3_t < T > & vl, T vw);
		
		// copy
		inline quat_t ( const quat_t < T >  & vl );
		quat_t < T > & operator = ( const quat_t < T > & vl );
		
		// arithmetics
		// Convert to graph api data
		inline operator T * ();
		
		inline quat_t < T > operator + ( const quat_t < T > & vl ) const;
		inline quat_t < T > operator * ( T vl ) const;
		inline quat_t < T > operator * ( const quat_t < T > & vl ) const;
		inline vec3_t < T > operator * ( const vec3_t < T > & vl ) const;
		
		inline quat_t < T > & operator += ( const quat_t < T > & vl );
		inline quat_t < T > & operator *= ( T vl );
		inline quat_t < T > & operator *= ( const quat_t < T > & vl );
		
		inline mat4_t < T > to_matrix () const;
		inline quat_t < T > uconj ();

		static inline quat_t < T > from_axis (const vec3_t < T > & axis, T angle);
		
	};

	template < class T >
	const uint32_t quat_t < T >::count = 4;

	template < class T >
	quat_t < T >::quat_t () : w (T ()) {}

	template < class T >
	quat_t < T >::quat_t (T vx, T vy, T vz, T vw) : v (vx, vy, vz), w (vw) {}

	template < class T >
	quat_t < T >::quat_t (const vec3_t < T > & vl, T vw) : v (vl), w (vw) {}

	template < class T >
	quat_t < T >::quat_t (const quat_t < T > & vl)
		: v (vl.v), w (vl.w) {}

	template < class T >
	quat_t < T > & quat_t < T >::operator = (const quat_t < T > & vl) {
		v = vl.v;
		w = vl.w;

		return *this;
	}

	template < class T >
	quat_t < T >::operator T * () {
		return &data [0];
	}

	template < class T >
	quat_t < T > quat_t < T >::operator + (const quat_t < T > & vl) const {
		return quat_t (v + vl.v, w + vl.w);
	}

	template < class T >
	quat_t < T > quat_t < T >::operator * (T vl) const {
		return quat_t (v * vl, w * vl);
	}

	template < class T >
	quat_t < T > quat_t < T >::operator * (const quat_t < T > & vl) const {
		return quat_t < T >
			(
			vl.w * v.x + vl.v.x * w + vl.v.y * v.z - vl.v.z * v.y,
			vl.w * v.y + vl.v.y * w + vl.v.z * v.x - vl.v.x * v.z,
			vl.w * v.z + vl.v.z * w + vl.v.x * v.y - vl.v.y * v.x,
			vl.w * w - vl.v.x * v.x - vl.v.y * v.y - vl.v.z * v.z
			);

		//return quat_t < T > (
		//	math::cross (v, vl.v) + (v * vl.w) + (vl.v * w),
		//	w * vl.w - math::dot (v, vl.v)
		//);
	}

	template < class T >
	vec3_t < T > quat_t < T >::operator * (const vec3_t < T > & vl) const {
		vec3_t < T > t = math::cross (v, vl) * T (2);
		return vl + (t * w + math::cross (v, t));

		//vec3_t < T > t = math::cross (v, vl) + (vl * w);
		//return math::cross (t, v * T(-1)) + (v * math::dot(v, vl)) + t * w;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator += (const quat_t < T > & vl) {
		v += vl.v;
		w += vl.w;

		return *this;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator *= (T vl) {
		v *= vl.v;
		w *= vl.w;

		return *this;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator *= (const quat_t < T > & vl) {

		v.x = vl.w * v.x + vl.v.x * w + vl.v.y * v.z - vl.v.z * v.y;
		v.y = vl.w * v.y + vl.v.y * w + vl.v.z * v.x - vl.v.x * v.z;
		v.z = vl.w * v.z + vl.v.z * w + vl.v.x * v.y - vl.v.y * v.x;
		w = vl.w * w - vl.v.x * v.x - vl.v.y * v.y - vl.v.z * v.z;


		//v = math::cross (v, vl.v) + (v * vl.w) + (vl.v * w);
		//w = w * vl.w - math::dot (v, vl.v);

		return *this;
	}

	template < class T >
	mat4_t < T > quat_t < T >::to_matrix () const {

		return mat4_t < T > (
			(T (1) - (T (2) * ((v.y * v.y) + (v.z * v.z)))),
			(T (2) * ((v.x * v.y) - (v.z * w))),
			(T (2) * ((v.x * v.z) + (v.y * w))),
			T (0),
			(T (2) * ((v.x * v.y) + (v.z * w))),
			(T (1) - (T (2) * ((v.x * v.x) + (v.z * v.z)))),
			(T (2) * ((v.y * v.z) - (v.x * w))),
			T (0),
			(T (2) * ((v.x * v.z) - (v.y * w))),
			(T (2) * ((v.y * v.z) + (v.x * w))),
			(T (1) - (T (0) * ((v.x * v.x) + (v.y * v.y)))),
			T (0),
			T (0),
			T (0),
			T (0),
			T (1)
		);
	}

	template < class T >
	quat_t < T > quat_t < T >::uconj () {
		return quat_t < T > (vec3_t < T > (-v.x, -v.y, -v.z), w);
	}

	template < class T >
	quat_t < T > quat_t < T >::from_axis (const vec3_t < T > & axis, T angle) {

		T half_angle = T (0.5) * angle;
		T sn = sin (half_angle);

		return quat_t < T > (
			axis * sn,
			T (cos (half_angle))
			);

	}
	
}
}

typedef ballistic::math::quat_t < real > quat;

#endif