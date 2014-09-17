#ifndef	_ballistic_math_quat_h_
#define _ballistic_math_quat_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"
#include "ballistic.math.h"
#include "ballistic.math.vectors.h"
#include "ballistic.math.matrixes.h"

namespace ballistic {
	namespace math {
		namespace details {

			template < class value_t >
			struct quat_t {

				static const uint32_t size = 4;

				union {
					value_t data [4];

					struct { value_t x, y, z, w; };

					vec3_t < value_t > xyz;
					vec4_t < value_t > xyzw;
				};

				inline mat4_t < value_t > to_matrix () const {
					return {
						(value_t (1) - (value_t (2) * ((y * y) + (z * z)))), (value_t (2) * ((x * y) + (z * w))), (value_t (2) * ((x * z) - (y * w))), value_t (0),
						(value_t (2) * ((x * y) - (z * w))), (value_t (1) - (value_t (2) * ((x * x) + (z * z)))), (value_t (2) * ((y * z) + (x * w))), value_t (0),
						(value_t (2) * ((x * z) + (y * w))), (value_t (2) * ((y * z) - (x * w))), (value_t (1) - (value_t (2) * ((x * x) + (y * y)))), value_t (0),
						value_t (0), value_t (0), value_t (0), value_t (1)
					};
				}

				inline quat_t < value_t > uconj () const {
					return{
						-x,
						-y,
						-z,
						w
					};
				}

				static inline quat_t < value_t > from_axis (const vec3_t < value_t > & axis, value_t angle) {
					value_t half_angle = value_t (0.5) * angle;
					value_t sn = sin (half_angle);

					quat_t < value_t > q;

					q.xyz = axis * sn;
					q.w = value_t (cos (half_angle));

					return q;
				}

				inline static bool parse (const tinyxml2::XMLAttribute * config_value, quat_t < value_t > & ret) {
					return convert_vectors < value_t, 4 > (config_value->Value (), ret.data);
				}

			};

			template < class value_t >
			inline quat_t < value_t > operator * (const quat_t < value_t > & v1, const quat_t < value_t > & v2) {
				return{
					v1.w * v2.x + v1.x * v2.w + v1.y * v2.z - v1.z * v2.y,
					v1.w * v2.y - v1.x * v2.z + v1.y * v2.w + v1.z * v2.x,
					v1.w * v2.z + v1.x * v2.y - v1.y * v2.x + v1.z * v2.w,
					v1.w * v2.w - v1.x * v2.x - v1.y * v2.y - v1.z * v2.z
				};
			}

			template < class value_t >
			inline vec3_t < value_t > operator * (const quat_t < value_t > & q, const vec3_t < value_t > & v) {
				vec3_t < value_t > r = math::cross (q.xyz, v) * value_t (2);
				return v + (r * q.w + math::cross (q.xyz, r));
			}

		}
	}

	typedef ballistic::math::details::quat_t < real > quat;
}

#endif