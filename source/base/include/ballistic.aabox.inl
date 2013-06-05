
namespace ballistic {

	aabox::aabox ( const vec3 pos, const vec3 & max ) : position (pos), max (max) {}

	aabox::aabox ( const aabox & v ) : position ( v.position ), max ( v.max ) {}

	aabox & aabox::operator = ( const aabox & v ) {
		position = v.position;
		max = v.max;

		return *this;
	}

	intersection_type aabox::intersect ( const aabox & box ) const {
		vec3 
			v_min = position - max,
			v_max = position + max,
			bb_min = box.position - box.max, 
			bb_max = box.position + box.max;

		if ( v_max.x - bb_min.x < 0.0F || bb_max.x - v_min.x < 0 )
			return intersection_none;

		if ( v_max.y - bb_min.y < 0 || bb_max.y - v_min.y < 0 )
			return intersection_none;

		if ( v_max.z - bb_min.z < 0 || bb_max.z - v_min.z < 0 )
			return intersection_none;

		if ( v_min.x <= bb_min.x && v_min.y <= bb_min.y && v_min.z <= bb_min.z &&
			v_max.x >= bb_max.x && v_max.y >= bb_max.y && max.z >= bb_max.z ) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	intersection_type aabox::intersect_axis_aligned ( const aabox & box, uint32 a_axis, uint32 b_axis ) const {
		vec3 
			v_min = position - max,
			v_max = position + max,
			bb_min = box.position - box.max, 
			bb_max = box.position + box.max;

		if ( v_max.data [a_axis] - bb_min.data [a_axis] < 0.0F || bb_max.data [a_axis] - v_min.data [a_axis] < 0 )
			return intersection_none;

		if ( v_max.z - bb_min.z < 0 || bb_max.data [b_axis] - v_min.data [b_axis] < 0 )
			return intersection_none;

		if ( v_min.data [a_axis] <= bb_min.data [a_axis] && v_min.data [b_axis] <= bb_min.data [b_axis] &&
			v_max.data [a_axis] >= bb_max.data [a_axis] && max.data [b_axis] >= bb_max.data [b_axis] ) {

			return intersection_contains;
		}

		return intersection_intersects;
	}

	intersection_type aabox::intersect_x_aligned ( const aabox & box ) const {
		return intersect_axis_aligned (box, axis_index_y, axis_index_z);
	}

	intersection_type aabox::intersect_y_aligned ( const aabox & box ) const {
		return intersect_axis_aligned (box, axis_index_x, axis_index_z);
	}

	intersection_type aabox::intersect_z_aligned ( const aabox & box ) const {
		return intersect_axis_aligned (box, axis_index_x, axis_index_y);
	}

	aabox aabox::operator + ( const vec3 & v ) const {
		return 
			aabox (position + v, max);
	}

	aabox aabox::operator - ( const vec3 & v ) const {
		return
			aabox (position - v, max);
	}
}