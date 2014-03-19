#ifndef _ballistic_animation_ianimation_h_
#define _ballistic_animation_ianimation_h_

#include "ballistic.config.h"
#include "ballistic.entity.h"
#include "ballistic.math.vecn_t.h"
#include "ballistic.math.vectors.h"
#include "ballistic.property.h"
#include "ballistic.property_container.h"

namespace ballistic {
	namespace animation {

		enum repeat_mode {
			repeat_mode_none,
			repeat_mode_loop,
			repeat_mode_reverse
		};

		class ianimation {
		public:

			virtual iproperty *  target () = 0;

			virtual void setup (entity * parent, property_container & parameters) = 0;

			virtual void update (real elapsed_time) = 0;

		};

		template < class target_value_t >
		class linear_animation : public ianimation {
		private:

			target_value_t					_start;
			target_value_t					_end;

			property < target_value_t > *	_target;

		public:

			inline virtual iproperty * target () {
				return _target;
			}

			inline virtual void setup (entity * parent, property_container & parameters) {

				_start	= *parameters.require < target_value_t > (id::start, target_value_t ());
				_end	= *parameters.require < target_value_t > (id::start, target_value_t ());

				id_t target_property_id = parameters.require < id_t > (id::target_id, id::null);

				if (target_property_id == id::null) {
					debug_print ("animation target property not set");
					_target = nullptr;
				} else {
					_target = parent->properties.require < target_value_t > (target_property_id, target_value_t);
				}
			}

			template < >
			inline target_value_t blend (real elapsed_time, real & start, real & end) {
				return start + (end - start) * elapsed_time;
			}

			template < class value_t, class data_t >
			inline math::vecn_t < value_t, data_t > blend (
				real elapsed_time,
				math::vecn_t < value_t, data_t > & start,
				math::vecn_t < value_t, data_t > & end
			) {
				vecn_t < value_t, data_t > res;
				
				for (int i = 0; i < data_t::size; ++i) {
					res.data [i] = blend (elapsed_time, start.data [i], end.data [i]);
				}

				return res;
			}

			inline virtual void update (real elapsed_time) {
				(*_target) = blend (elapsed_time, *_target, _start, _end);
			}

		}; 

		template < class target_value_t >
		class bezier_animation : public ianimation {
		private:

			target_value_t					_start;
			target_value_t					_end;

			target_value_t					_cp1;
			target_value_t					_cp2;

			property < target_value_t > *	_target;

		public:

			inline virtual iproperty * target () {
				return _target;
			}

			inline virtual void setup (entity * parent, property_container & parameters) {

				_start = *parameters.require < target_value_t > (id::start, target_value_t ());
				_end = *parameters.require < target_value_t > (id::start, target_value_t ());
				_cp1 = *parameters.require < target_value_t > (id::control_1, _start);
				_cp2 = *parameters.require < target_value_t > (id::control_2, _end);

				id_t target_property_id = parameters.require < id_t > (id::target_id, id::null);

				if (target_property_id == id::null) {
					debug_print ("animation target property not set");
					_target = nullptr;
				} else {
					_target = parent->properties.require < target_value_t > (target_property_id, target_value_t);
				}
			}

			template < >
			inline target_value_t blend (real elapsed_time, real & start, real & cp1, real & cp2, real & end) {
				return 
					std::pow (real (1) - t, real (2)) * start + real (3) *
					std::pow (real (1) - t, real (3)) * t * cp1 + 3 * (real (1) - t) *
					std::pow (t, real (2)) * cp2 +
					std::pow (t, real (3)) * end;
			}

			template < class value_t, class data_t >
			inline math::vecn_t < value_t, data_t > blend (
				real elapsed_time,
				math::vecn_t < value_t, data_t > & start,
				math::vecn_t < value_t, data_t > & end
				) {
				vecn_t < value_t, data_t > res;

				for (int i = 0; i < data_t::size; ++i) {
					res.data [i] = blend (elapsed_time, start.data [i], end.data [i], cp1.data [i], cp2.data [i]);
				}

				return res;
			}

			inline virtual void update (real elapsed_time) {
				(*_target) = blend (elapsed_time, *_target, _start, _end, _cp1, _cp2);
			}

		};

		typedef linear_animation < real >	real_linear_animation;
		typedef linear_animation < vec2 >	vec2_linear_animation;
		typedef linear_animation < vec3 >	vec3_linear_animation;
		typedef linear_animation < color >	color_linear_animation;

		typedef bezier_animation < real >	real_bezier_animation;
		typedef bezier_animation < vec2 >	vec2_bezier_animation;
		typedef bezier_animation < vec3 >	vec3_bezier_animation;
		typedef bezier_animation < color >	color_bezier_animation;

	}
}

#endif