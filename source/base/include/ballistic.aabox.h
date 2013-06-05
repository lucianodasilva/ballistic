#ifndef	_ballistic_aabox_h_
#define _ballistic_aabox_h_

#include "ballistic.vectors.h"

namespace ballistic {

	enum intersection_type : uint32 {
		intersection_none,
		intersection_contains,
		intersection_intersects
	};

	struct aabox {

		vec3 position, max;
		
		inline aabox ( const vec3 pos, const vec3 & max );
		inline aabox ( const aabox & v );

		inline aabox & operator = ( const aabox & v );

		inline intersection_type intersect ( const aabox & box ) const;

		inline intersection_type intersect_axis_aligned ( const aabox & box, uint32 a_axis, uint32 b_axis ) const;

		inline intersection_type intersect_x_aligned ( const aabox & box ) const;
		inline intersection_type intersect_y_aligned ( const aabox & box ) const;
		inline intersection_type intersect_z_aligned ( const aabox & box ) const;

		// Transform operators
		inline aabox operator + ( const vec3 & v ) const;
		inline aabox operator - ( const vec3 & v ) const;

	};

}

#include "ballistic.aabox.inl"

#endif