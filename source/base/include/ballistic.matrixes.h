#ifndef	_ballistic_h_
#define _ballistic_h_

#include "ballistic.config.h"
#include "ballistic.vectors.h"

struct mat4 {

	static const uint32 data_length = 16;

	union {
		real data [data_length];

		struct {
			real m00, m01, m02, m03;
			real m04, m05, m06, m07;
			real m08, m09, m10, m11;
			real m12, m13, m14, m15;
		};
	};


	inline mat4 ();

	inline mat4 ( const mat4 & v );
	inline mat4 ( real _m00, real _m01, real _m02, real _m03, real _m04, real _m05, real _m06, real _m07, real _m08, real _m09, real _m10, real _m11, real _m12, real _m13, real _m14, real _m15 );

	inline mat4 & operator = ( const mat4 & v );

	inline mat4 operator * ( const mat4 & v ) const;
	inline vec4 operator * ( const vec4 & v ) const;
	inline vec3 operator * ( const vec3 & v ) const;

	inline mat4 transpose () const;

	// Create matrixes
	static mat4 make_translation ( const vec3 & p );
	static mat4 make_translation ( const vec4 & p );

	static mat4 make_rotation_x ( real r );
	static mat4 make_rotation_y ( real r );
	static mat4 make_rotation_z ( real r );

	static mat4 make_scale ( const vec3 & p );
	static mat4 make_scale ( const vec4 & p );
};

#include "ballistic.matrixes.inl"

#endif