#ifndef _ballistic_vec3_h_
#define _ballistic_vec3_h_

#include "ballistic.config.h"

enum axis_index : uint32 {
	axis_index_x = 0U,
	axis_index_y = 1U,
	axis_index_z = 2U
};

struct vec2 {

	union {
		real data [2];
		struct { real x, y; };
	};

	inline vec2 ( real vx, real vy );
	inline vec2 ( );

	// copy
	inline vec2 ( const vec2 & v );
	inline vec2 & operator = ( vec2 v );

	// access
	inline operator real * ();

	// basic arithmetics
	inline vec2 operator + ( const vec2 & v ) const;
	inline vec2 operator - ( const vec2 & v ) const;
	inline vec2 operator * ( real v ) const;
	inline vec2 operator / ( real v ) const;

	inline vec2 & operator += ( const vec2 & v );
	inline vec2 & operator -= ( const vec2 & v );
	inline vec2 & operator *= ( real v );
	inline vec2 & operator /= ( real v );
};

struct vec3 {

	union {
		real data [3];
		struct { real x, y, z; };
		struct { real r, g, b; };
	};

	inline vec3 (real vx, real vy, real vz);
	inline vec3 ();

	// copy
	inline vec3 ( const vec3 & v );
	inline vec3 & operator = ( vec3 v );

	// Convert to graph api data
	inline operator real * ();

	inline vec3 operator + ( const vec3 & v ) const;
	inline vec3 operator - ( const vec3 & v ) const;
	inline vec3 operator * ( real v ) const;
	inline vec3 operator / ( real v ) const;

	inline vec3 & operator += ( const vec3 & v );
	inline vec3 & operator -= ( const vec3 & v );
	inline vec3 & operator *= ( real v );
	inline vec3 & operator /= ( real v );

};

struct vec4 {

	union {
		real data [4];
		struct { real x, y, z, w;};
#if defined (BALLISTIC_DIRECTX)
		struct { real a, r, g, b; };
#elif defined (BALLISTIC_OPENGL)
		struct { real r, g, b, a; };
#endif
	};

	inline vec4 (real vx, real vy, real vz, real vw);
	inline vec4 ();

	inline vec4 ( const vec4 & v );
	inline vec4 & operator = ( vec4 v );

	// Convert to graph api data
	inline operator real * ();

	inline vec4 operator + ( const vec4 & v ) const;
	inline vec4 operator - ( const vec4 & v ) const;
	inline vec4 operator * ( real v ) const;
	inline vec4 operator / ( real v ) const;

	inline vec4 & operator += ( const vec4 & v );
	inline vec4 & operator -= ( const vec4 & v );
	inline vec4 & operator *= ( real v );
	inline vec4 & operator /= ( real v );

};

#include "ballistic.vectors.inl"

typedef vec4 color;

#endif