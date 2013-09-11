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
		
		static const uint32 count;
		
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
	
}
}

#include "ballistic.math.quat.inl"

typedef ballistic::math::quat_t < real > quat;

#endif