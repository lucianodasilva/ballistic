
namespace ballistic {
	namespace math {

	template < class T >
	aabox_t < T >::aabox_t ( const vec3_t < T > & min, const vec3_t < T > & max ) : min (min), max (max) {}

	template < class T >
	aabox_t < T >::aabox_t ( const aabox_t < T > & v ) : min ( v.min ), max ( v.max ) {}

	template < class T >
	aabox_t < T > & aabox_t < T >::operator = ( const aabox_t < T > & v ) {
		min = v.min;
		max = v.max;

		return *this;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect ( const aabox_t < T > & box ) const {

		if ( max.x - box.min.x < 0.0F || box.max.x -min.x < 0 )
			return intersection_none;

		if ( max.y - box.min.y < 0 || box.max.y - min.y < 0 )
			return intersection_none;

		if ( max.z - box.min.z < 0 || box.max.z - min.z < 0 )
			return intersection_none;

		if ( min.x <= box.min.x && min.y <= box.min.y && min.z <= box.min.z &&
			max.x >= box.max.x && max.y >= box.max.y && max.z >= box.max.z ) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_axis_aligned ( const aabox_t < T > & box, uint32 a_axis, uint32 b_axis ) const {

		if ( max.data [a_axis] - box.min.data [a_axis] < 0.0F || box.max.data [a_axis] - min.data [a_axis] < 0 )
			return intersection_none;

		if ( max.z - box.min.z < 0 || box.max.data [b_axis] - min.data [b_axis] < 0 )
			return intersection_none;

		if ( min.data [a_axis] <= box.min.data [a_axis] && min.data [b_axis] <= box.min.data [b_axis] &&
			max.data [a_axis] >= box.max.data [a_axis] && max.data [b_axis] >= box.max.data [b_axis] ) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_x_aligned ( const aabox_t < T > & box ) const {
		return intersect_axis_aligned (
			box, 
			ballistic::math::axis_index_y, 
			ballistic::math::axis_index_z
		);
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_y_aligned ( const aabox_t < T > & box ) const {
		return intersect_axis_aligned (
			box, 
			ballistic::math::axis_index_x, 
			ballistic::math::axis_index_z
		);
	}

	template < class T >
	intersection_type aabox_t < T >::intersect_z_aligned ( const aabox_t < T > & box ) const {
		return intersect_axis_aligned (
			box, 
			ballistic::math::axis_index_x, 
			ballistic::math::axis_index_y
		);
	}

	template < class T >
	aabox_t < T > aabox_t < T >::operator + ( const vec3_t < T > & v ) const {
		return 
			aabox_t (min + v, max + v);
	}

	template < class T >
	aabox_t < T > aabox_t < T >::operator - ( const vec3_t < T > & v ) const {
		return
			aabox_t (min - v, max + v);
	}
}
}