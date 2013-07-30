#ifndef	_ballistic_math_quat_h_
#define _ballistic_math_quat_h_

#include "ballistic.config.h"
#include "ballistic.math.h"

namespace ballistic {
namespace math {

	template < class T >
	struct quat_t {
		
		typedef T type;
		
		const uint32 count;
		
		union {
			T data [4];
			struct { T x, y, z, w; };
		}
		
		// constructor
		inline quat_t ();
		inline quat_t ( T x, T y, T z, T w )t
		
		// copy
		inline quat_t ( const quat_t < T >  & v );
		quat_t < T > & operator = ( const quat_t < T > & v );
		
		// arithmetics
		// Convert to graph api data
		inline operator T * ();
		
		inline quat_t < T > operator + ( const quat_t < T > & v ) const;
		inline quat_t < T > operator * ( T v ) const;
		inline quat_t < T > operator * ( const quat_t < T > & v ) const;
		inline vec3_t < T > operator * ( const vec3_t < T > & v ) const;
		
		inline quat_t < T > & operator += ( const quat_t < T > & v );
		inline quat_t < T > & operator *= ( T v );
		inline quat_t < T > & operator *= ( const quat_t < T > & v );
		
		inline mat4_t < T > to_matrix () const;
	};
	
}
}

#include "ballistic.math.quat.h"

typedef ballistic::math::quat_t < real > quat;

#endif