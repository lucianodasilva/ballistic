#ifndef _ballistic_math_vectors_h_
#define _ballistic_math_vectors_h_

#include "ballistic.config.h"

#include <string>
#include <tinyxml2.h>

using namespace std;

namespace ballistic {
	namespace math {

		enum axis_index : uint32_t {
			axis_index_x = 0U,
			axis_index_y = 1U,
			axis_index_z = 2U,
			axis_index_w = 3U
		};

		namespace details {

			template < class value_t >
			struct vec2_t {

				static const uint32_t size = 2;

				union {
					value_t data [size];
					struct { value_t x, y; };
				};

				inline static bool parse (const tinyxml2::XMLAttribute * config_value, vec2_t < value_t > & ret) {
					return convert_vectors < value_t, size > (config_value->Value (), ret.data);
				}

			};

			template < class value_t >
			struct vec3_t {

				static const uint32_t size = 3;

				union {
					value_t data [size];
					struct { value_t x, y, z; };
					struct { value_t r, g, b; };

					vec2_t < value_t > xy;
				};

				inline static bool parse (const tinyxml2::XMLAttribute * config_value, vec3_t < value_t > & ret) {
					return convert_vectors < value_t, size > (config_value->Value (), ret.data);
				}

			};

			template < class value_t >
			struct vec4_t {

				static const uint32_t size = 4;

				union {
					value_t data [size];
					struct { value_t x, y, z, w; };
					struct { value_t r, g, b, a; };

					vec2_t < value_t > xy;
					vec3_t < value_t > xyz;

					vec3_t < value_t > rgb;
				};

				inline static bool parse (const tinyxml2::XMLAttribute * config_value, vec4_t < value_t > & ret) {
					return convert_vectors < value_t, size > (config_value->Value (), ret.data);
				}

			};

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator + (const struct_t < value_t > & v1, const struct_t < value_t > & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] + v2.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator + (const struct_t < value_t > & v1, const value_t & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] + v2;

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator - (const struct_t < value_t > & v1, const struct_t < value_t > & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] - v2.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator - (const struct_t < value_t > & v1, const value_t & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] - v2;

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator * (const struct_t < value_t > & v1, const struct_t < value_t > & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] * v2.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator * (const struct_t < value_t > & v, const value_t & s) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v.data [i] * s;

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator * (const value_t & s, const struct_t < value_t > & v) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = s * v.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator / (const struct_t < value_t > & v1, const struct_t < value_t > & v2) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v1.data [i] / v2.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator / (const struct_t < value_t > & v, const value_t & s) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = v.data [i] / s;

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator / (const value_t & s, const struct_t < value_t > & v) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = s / v.data [i];

				return r;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > operator - (const struct_t < value_t > & v) {
				struct_t < value_t > r;

				for (int i = 0; i < struct_t < value_t >::size; ++i)
					r.data [i] = -v.data [i];

				return r;
			}

		}

	}

	typedef math::details::vec2_t < int32_t > point;

	typedef math::details::vec2_t < real > vec2;
	typedef math::details::vec3_t < real > vec3;
	typedef math::details::vec4_t < real > vec4;

	typedef math::details::vec2_t < int32_t > ivec2;
	typedef math::details::vec3_t < int32_t > ivec3;
	typedef math::details::vec4_t < int32_t > ivec4;

	typedef math::details::vec2_t < uint32_t > uvec2;
	typedef math::details::vec3_t < uint32_t > uvec3;
	typedef math::details::vec4_t < uint32_t > uvec4;

	typedef math::details::vec4_t < real > color;

}

#endif