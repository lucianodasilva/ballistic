#ifndef	_ballistic_math_aabox_t_h_
#define _ballistic_math_aabox_t_h_

#include "ballistic.math.vectors.h"

namespace ballistic {
namespace math {

	enum intersection_type : uint32_t {
		intersection_none,
		intersection_contains,
		intersection_intersects
	};

	template < class T >
	struct aabox_t {

		vec3_t < T > v_min, v_max;
		
		inline aabox_t ( const vec3_t < T > & v_min, const vec3_t < T > & v_max );
		inline aabox_t ( const aabox_t < T > & v );

		inline aabox_t < T > & operator = ( const aabox_t < T > & v );

		inline intersection_type intersect ( const aabox_t < T > & box ) const;

		inline intersection_type intersect_axis_aligned ( const aabox_t < T > & box, uint32_t a_axis, uint32_t b_axis ) const;

		inline intersection_type intersect_x_aligned ( const aabox_t < T > & box ) const;
		inline intersection_type intersect_y_aligned ( const aabox_t < T > & box ) const;
		inline intersection_type intersect_z_aligned ( const aabox_t < T > & box ) const;

		// Transform operators
		inline aabox_t < T > operator + ( const vec3_t < T > & v ) const;
		inline aabox_t < T > operator - ( const vec3_t < T > & v ) const;

	};

}
}

#include "ballistic.math.aabox.inl"

typedef ballistic::math::aabox_t < real > aabox;

#endif