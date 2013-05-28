#ifndef _ballistic_vec3_h_
#define _ballistic_vec3_h_

#include "ballistic.config.h"

struct vec3 {
	
	real x, y, z;

	inline vec3 (real vx, real vy, real vz);
	inline vec3 ();

	// Convert to graph api data
	inline operator real * ();

	inline vec3 operator + ( const vec3 & v ) const;
	inline vec3 operator - ( const vec3 & v ) const;
	inline vec3 operator * ( real v ) const;
	inline vec3 operator / ( real v ) const;

};

#include "ballistic.vec3.inl"

#endif