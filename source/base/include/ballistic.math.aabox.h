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

	template < class T >
	aabox_t < T >::aabox_t (const vec3_t < T > & v_min, const vec3_t < T > & v_max) : v_min (v_min), v_max (v_max) {}

	template < class T >
	aabox_t < T >::aabox_t (const aabox_t < T > & v) : v_min (v.v_min), v_max (v.v_max) {}

	template < class T >
	aabox_t < T > & aabox_t < T >::operator = (const aabox_t < T > & v) {
		v_min = v.v_min;
		v_max = v.v_max;

		return *this;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect (const aabox_t < T > & box) const {

		if (v_max.x - box.v_min.x < 0.0F || box.v_max.x - v_min.x < 0)
			return intersection_none;

		if (v_max.y - box.v_min.y < 0 || box.v_max.y - v_min.y < 0)
			return intersection_none;

		if (v_max.z - box.v_min.z < 0 || box.v_max.z - v_min.z < 0)
			return intersection_none;

		if (v_min.x <= box.v_min.x && v_min.y <= box.v_min.y && v_min.z <= box.v_min.z &&
			v_max.x >= box.v_max.x && v_max.y >= box.v_max.y && v_max.z >= box.v_max.z) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_axis_aligned (const aabox_t < T > & box, uint32_t a_axis, uint32_t b_axis) const {

		if (v_max.data [a_axis] - box.v_min.data [a_axis] < 0.0F || box.v_max.data [a_axis] - v_min.data [a_axis] < 0)
			return intersection_none;

		if (v_max.z - box.v_min.z < 0 || box.v_max.data [b_axis] - v_min.data [b_axis] < 0)
			return intersection_none;

		if (v_min.data [a_axis] <= box.v_min.data [a_axis] && v_min.data [b_axis] <= box.v_min.data [b_axis] &&
			v_max.data [a_axis] >= box.v_max.data [a_axis] && v_max.data [b_axis] >= box.v_max.data [b_axis]) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_x_aligned (const aabox_t < T > & box) const {
		return intersect_axis_aligned (
			box,
			ballistic::math::axis_index_y,
			ballistic::math::axis_index_z
			);
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_y_aligned (const aabox_t < T > & box) const {
		return intersect_axis_aligned (
			box,
			ballistic::math::axis_index_x,
			ballistic::math::axis_index_z
			);
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_z_aligned (const aabox_t < T > & box) const {
		return intersect_axis_aligned (
			box,
			ballistic::math::axis_index_x,
			ballistic::math::axis_index_y
			);
	}

	template < class T >
	aabox_t < T > aabox_t < T >::operator + (const vec3_t < T > & v) const {
		return
			aabox_t (v_min + v, v_max + v);
	}

	template < class T >
	aabox_t < T > aabox_t < T >::operator - (const vec3_t < T > & v) const {
		return
			aabox_t (v_min - v, v_max + v);
	}

}
}

typedef ballistic::math::aabox_t < real > aabox;

#endif