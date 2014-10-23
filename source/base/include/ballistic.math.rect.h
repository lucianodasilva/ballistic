#ifndef	_ballistic_math_rect_h_
#define _ballistic_math_rect_h_

#include "ballistic.math.vectors.h"

namespace ballistic {
	namespace math {
		namespace details {

			template < class value_t >
			struct rect_t {

				union {
					struct { 
						value_t 
							x, y, 
							width, height; 
					};

					struct { 
						vec2_t < value_t > 
							position, 
							size; 
					};
				};

				inline bool contains (const vec2_t < value_t > & v) const {
					return
						v.x >= x &&
						v.y >= y &&
						v.x <= x + width &&
						v.y <= y + height;
				}

			};

		}
	}

	typedef ballistic::math::details::rect_t < real > rect;
	typedef ballistic::math::details::rect_t < int32_t > irect;

}


#endif