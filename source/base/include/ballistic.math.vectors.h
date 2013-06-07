#ifndef _ballistic_math_vec3_t_h_
#define _ballistic_math_vec3_t_h_

#include "ballistic.config.h"

namespace ballistic {
namespace math {

	enum axis_index : uint32 {
		axis_index_x = 0U,
		axis_index_y = 1U,
		axis_index_z = 2U
	};

	template < class T = real >
	struct vec2_t {

		typedef T type;

		static const uint32 count;

		static const vec2_t < T > zero;
		static const vec2_t < T > one;

		union {
			T data [2];
			struct { T x, y; };
		};

		inline vec2_t ( T vx, T vy );
		inline vec2_t ( );

		// copy
		inline vec2_t ( const vec2_t < T > & v );
		inline vec2_t < T > & operator = ( vec2_t < T > v );

		// access
		inline operator T * ();

		// basic arithmetics
		inline vec2_t < T > operator + ( const vec2_t < T > & v ) const;
		inline vec2_t < T > operator - ( const vec2_t < T > & v ) const;
		inline vec2_t < T > operator * ( T v ) const;
		inline vec2_t < T > operator / ( T v ) const;

		inline vec2_t < T > & operator += ( const vec2_t < T > & v );
		inline vec2_t < T > & operator -= ( const vec2_t < T > & v );
		inline vec2_t < T > & operator *= ( T v );
		inline vec2_t < T > & operator /= ( T v );
	};

	template < class T = real >
	struct vec3_t {

		typedef T type;

		static const uint32 count;

		static const vec3_t < T > zero;
		static const vec3_t < T > one;

		union {
			T data [3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		inline vec3_t (T vx, T vy, T vz);
		inline vec3_t ();

		// copy
		inline vec3_t ( const vec3_t < T > & v );
		inline vec3_t & operator = ( vec3_t < T > v );

		// Convert to graph api data
		inline operator T * ();

		inline vec3_t < T > operator + ( const vec3_t < T > & v ) const;
		inline vec3_t < T > operator - ( const vec3_t < T > & v ) const;
		inline vec3_t < T > operator * ( T v ) const;
		inline vec3_t < T > operator / ( T v ) const;

		inline vec3_t < T > & operator += ( const vec3_t < T > & v );
		inline vec3_t < T > & operator -= ( const vec3_t < T > & v );
		inline vec3_t < T > & operator *= ( T v );
		inline vec3_t < T > & operator /= ( T v );

	};

	template < class T = real >
	struct vec4_t {

		typedef T type;

		static const uint32 count;

		static const vec4_t < T > zero;
		static const vec4_t < T > one;

		union {
			T data [4];
			struct { T x, y, z, w;};
	#if defined (BALLISTIC_DIRECTX)
			struct { T a, r, g, b; };
	#elif defined (BALLISTIC_OPENGL)
			struct { T r, g, b, a; };
	#endif
		};

		inline vec4_t (T vx, T vy, T vz, T vw);
		inline vec4_t ();

		inline vec4_t ( const vec4_t < T > & v );
		inline vec4_t < T > & operator = ( vec4_t < T > v );

		// Convert to graph api data
		inline operator T * ();

		inline vec4_t < T > operator + ( const vec4_t < T > & v ) const;
		inline vec4_t < T > operator - ( const vec4_t < T > & v ) const;
		inline vec4_t < T > operator * ( T v ) const;
		inline vec4_t < T > operator / ( T v ) const;

		inline vec4_t < T > & operator += ( const vec4_t < T > & v );
		inline vec4_t < T > & operator -= ( const vec4_t < T > & v );
		inline vec4_t < T > & operator *= ( T v );
		inline vec4_t < T > & operator /= ( T v );

	};
}
}

#include "ballistic.math.vectors.inl"

typedef ballistic::math::vec4_t < real > color;

typedef ballistic::math::vec2_t < int32 > point;

typedef ballistic::math::vec2_t < real > vec2;
typedef ballistic::math::vec3_t < real > vec3;
typedef ballistic::math::vec4_t < real > vec4;

#endif