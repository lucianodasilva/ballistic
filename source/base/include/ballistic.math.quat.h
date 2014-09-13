#ifndef	_ballistic_math_quat_h_
#define _ballistic_math_quat_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"
#include "ballistic.math.h"
#include "ballistic.math.vectors.h"
#include "ballistic.math.matrixes.h"

namespace ballistic {
namespace math {

	template < class T >
	struct quat_t {
		
		static const uint32_t size = 4;
		
		union {
			T data [4];

			struct { T x, y, z, w; };

			vectors::vec3_t < T > xyz;
			vectors::vec4_t < T > xyzw;
		};
		
		// arithmetics
		
		inline quat_t < T > operator + ( const quat_t < T > & vl ) const;
		inline quat_t < T > operator - (const quat_t < T > & vl) const;
		inline quat_t < T > operator * ( const quat_t < T > & vl ) const;
		inline vectors::vec3_t < T > operator * ( const vectors::vec3_t < T > & vl ) const;
		
		inline mat4_t < T > to_matrix () const;
		inline quat_t < T > uconj () const;

		static inline quat_t < T > from_axis (const vectors::vec3_t < T > & axis, T angle);

		inline static bool parse (const tinyxml2::XMLAttribute * config_value, quat_t < T > & ret);
		
	};

	template < class T >
	quat_t < T > quat_t < T >::operator + (const quat_t < T > & vl) const {
		quat_t < T > r;
		r.xyzw = xyzw + vl.xyzw;
		return r;
	}

	template < class T >
	quat_t < T > quat_t < T >::operator - (const quat_t < T > & vl) const {
		quat_t < T > r;
		r.xyzw = xyzw - vl.xyzw;
		return r;
	}

	//template < class T >
	//quat_t < T > quat_t < T >::operator * (T vl) const {
	//	quat_t < T > r;
	//	r.xyzw = xyzw * vl.xyzw;
	//	return r;
	//}

	template < class T >
	quat_t < T > quat_t < T >::operator * (const quat_t < T > & vl) const {
		return{
			w * vl.x + x * vl.w + y * vl.z - z * vl.y,
			w * vl.y - x * vl.z + y * vl.w + z * vl.x,
			w * vl.z + x * vl.y - y * vl.x + z * vl.w,
			w * vl.w - x * vl.x - y * vl.y - z * vl.z
		};
	}

	template < class T >
	vectors::vec3_t < T > quat_t < T >::operator * (const vectors::vec3_t < T > & vl) const {
		vectors::vec3_t < T > t = math::cross (xyz, vl) * T (2);
		return vl + (t * w + math::cross (xyz, t));
	}

	template < class T >
	mat4_t < T > quat_t < T >::to_matrix () const {

		return mat4_t < T > ({
			(T (1) - (T (2) * ((y * y) + (z * z)))), (T (2) * ((x * y) + (z * w))), (T (2) * ((x * z) - (y * w))), T (0),
			(T (2) * ((x * y) - (z * w))), (T (1) - (T (2) * ((x * x) + (z * z)))), (T (2) * ((y * z) + (x * w))), T (0),
			(T (2) * ((x * z) + (y * w))), (T (2) * ((y * z) - (x * w))), (T (1) - (T (2) * ((x * x) + (y * y)))), T (0),
			T (0), T (0), T (0), T (1)
		});
	}

	template < class T >
	quat_t < T > quat_t < T >::uconj () const {
		return{
			-x,
			-y,
			-z,
			w
		};
	}

	template < class T >
	quat_t < T > quat_t < T >::from_axis (const vectors::vec3_t < T > & axis, T angle) {

		T half_angle = T (0.5) * angle;
		T sn = sin (half_angle);

		quat_t < T > q;

		q.xyz = axis * sn;
		q.w = T (cos (half_angle));

		return q;
	}

	template < class T >
	bool quat_t < T >::parse (const tinyxml2::XMLAttribute * config_value, quat_t < T > & ret) {
		return convert_vectors < T, 4 > (config_value->Value (), ret.data);
	}
	
}
}

typedef ballistic::math::quat_t < real > quat;

#endif