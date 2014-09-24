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

	namespace details {

		template < class value_t >
		struct aabox_t {

			vec3_t < value_t > v_min, v_max;

			inline intersection_type intersect (const aabox_t < value_t > & box) const {
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

			inline intersection_type intersect_axis_aligned (const aabox_t < value_t > & box, uint32_t a_axis, uint32_t b_axis) const {
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

			inline intersection_type intersect_x_aligned (const aabox_t < value_t > & box) const {
				return intersect_axis_aligned (
					box,
					ballistic::math::axis_index_y,
					ballistic::math::axis_index_z
				);
			}

			inline intersection_type intersect_y_aligned (const aabox_t < value_t > & box) const {
				return intersect_axis_aligned (
					box,
					ballistic::math::axis_index_x,
					ballistic::math::axis_index_z
				);
			}

			inline intersection_type intersect_z_aligned (const aabox_t < value_t > & box) const {
				return intersect_axis_aligned (
					box,
					ballistic::math::axis_index_x,
					ballistic::math::axis_index_y
				);
			}

			inline void wrap (const vec3 & p) {
				if (p.x < v_min.x) v_min.x = p.x;
				if (p.y < v_min.y) v_min.y = p.y;
				if (p.z < v_min.z) v_min.z = p.z;
				if (p.x > v_max.x) v_max.x = p.x;
				if (p.y > v_max.y) v_max.y = p.y;
				if (p.z > v_max.z) v_max.z = p.z;
			}

		};

		template < class value_t >
		aabox_t < value_t > operator + (const aabox_t < value_t > & b, const vec3_t < value_t > & v)  {
			return {
				b.v_min + v, 
				b.v_max + v
			};
		}

		template < class value_t >
		aabox_t < value_t > operator - (const aabox_t < value_t > & b, const vec3_t < value_t > & v) {
			return {
				b.v_min - v, 
				b.v_max - v
			};
		}

		template < class value_t >
		aabox_t < value_t > operator * (const aabox_t < value_t > & b, const value_t & v) {
			return{
				b.v_min * v,
				b.v_max * v
			};
		}

		template < class value_t >
		aabox_t < value_t > operator / (const aabox_t < value_t > & b, const value_t & v) {
			return{
				b.v_min / v,
				b.v_max / v
			};
		}
	}

}
	using aabox = ballistic::math::details::aabox_t < real >;
}



#endif