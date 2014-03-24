#ifndef _ballistic_math_vectors_h_
#define _ballistic_math_vectors_h_

#include "ballistic.config.h"
#include "ballistic.math.vecn_t.h"

#include <string>

using namespace std;

namespace ballistic {
namespace math {

	enum axis_index : uint32_t {
		axis_index_x = 0U,
		axis_index_y = 1U,
		axis_index_z = 2U
	};

	namespace details {

		template < class value_t > 
		struct vec2_data_t {
			const static uint32_t size = 2;

			union {
				struct { value_t v1, v2;  } copy_handle;
				// accessors
				value_t data [size];
				struct {
					value_t x, y;
				};
			};
		};

		template < class value_t > 
		struct vec3_data_t {
			const static uint32_t size = 3;

			union {
				struct { value_t v1, v2, v3; } copy_handle;
				// accessors
				value_t data [size];
				struct {
					value_t x, y, z;
				};
			};
		};

		template < class value_t > 
		struct vec4_data_t {
			const static uint32_t size = 4;

			union {
				struct { value_t v1, v2, v3, v4; } copy_handle;
				// accessors
				value_t data [size];
				struct {
					value_t x, y, z, w;
				};
			};
		};

	}

	template < class value_t >
	using vec2_t = vecn_t < value_t, details::vec2_data_t < value_t > >;

	template < class value_t >
	using vec3_t = vecn_t < value_t, details::vec3_data_t < value_t > >;

	template < class value_t >
	using vec4_t = vecn_t < value_t, details::vec4_data_t < value_t > >;

}

	namespace details {
		template < class value_t > 
		struct color_data_t {
			const static uint32_t size = 4;

			union {
				struct { value_t v1, v2, v3, v4; } copy_handle;
				// accessors
				value_t data [size];
				struct {
					value_t r, g, b, a;
				};
			};
		};

		template < class value_t >
		using color_t = ballistic::math::vecn_t < value_t, color_data_t < value_t > >;
	}

	typedef math::vec2_t < int32_t > point;

	typedef math::vec2_t < real > vec2;
	typedef math::vec3_t < real > vec3;
	typedef math::vec4_t < real > vec4;

	typedef details::color_t < real > color;

}

#endif