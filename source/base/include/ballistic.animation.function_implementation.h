#ifndef _ballistic_animation_function_implementatino_h_
#define _ballistic_animation_function_implementatino_h_

#include "ballistic.config.h"
#include "ballistic.animation.function.h"
#include "ballistic.animation.driver.h"
#include "ballistic.animation.storyboard.h"

namespace ballistic {
	namespace animation {

		template < class target_value_t >
		class function_abstract : public function < target_value_t > {

			inline virtual idriver * create_driver (storyboard::action & action, entity * target, const id_t property_id) {
				return new driver < target_value_t > (
					action,
					target->properties.aquire < target_value_t > (property_id),
					this
				);
			}

		};

		template < class target_value_t >
		class linear_function : public function_abstract < target_value_t > {
		private:

			target_value_t					_start;
			target_value_t					_end;

		public:

			inline static void require_parameters (containers::property_container & parameters) {
				parameters
					.require < target_value_t > (id::animation::start)
					.template require < target_value_t > (id::animation::end);
			}

			inline virtual void setup (containers::property_container & parameters) override {
				_start = parameters[id::animation::start];
				_end = parameters [id::animation::end];
			}

			template < class value_t >
			inline value_t blend (value_t t, value_t & start, value_t & end) {
				return start + (end - start) * t;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > blend (
				real t,
				struct_t < value_t > & start,
				struct_t < value_t > & end
				) {

				struct_t < value_t > res;

				for (int i = 0; i < struct_t < value_t >::size; ++i) {
					res.data [i] = blend < value_t > (t, start.data [i], end.data [i]);
				}

				return res;
			}

			inline virtual void update (real t, property < target_value_t > * target) override {
				(*target) = blend (t, _start, _end);
			}

		};

		template < class target_value_t >
		class bezier_function : public function_abstract < target_value_t > {
		private:

			target_value_t					_start;
			target_value_t					_end;

			target_value_t					_cp1;
			target_value_t					_cp2;

		public:

			inline static void require_parameters (containers::property_container & parameters) {
				parameters
					.template require < target_value_t > (id::animation::start)
					.template require < target_value_t > (id::animation::end)
					.template require < target_value_t > (id::animation::control_1)
					.template require < target_value_t > (id::animation::control_2);
			}

			inline virtual void setup (containers::property_container & parameters) override {
				_start = parameters[id::animation::start];
				_end = parameters[id::animation::end];
				_cp1 = parameters[id::animation::control_1];
				_cp2 = parameters[id::animation::control_2];
			}

			template < class value_t >
			inline value_t blend (value_t t, value_t & start, value_t & cp1, value_t & cp2, value_t & end) {
				return
					std::pow (value_t (1) - t, value_t (2)) * start + value_t (3) *
					std::pow (value_t (1) - t, value_t (3)) * t * cp1 + 3 * (value_t (1) - t) *
					std::pow (t, value_t (2)) * cp2 +
					std::pow (t, value_t (3)) * end;
			}

			template < class value_t, template < class > class struct_t >
			inline struct_t < value_t > blend (
				real t,
				struct_t < value_t > & start,
				struct_t < value_t > & cp1,
				struct_t < value_t > & cp2,
				struct_t < value_t > & end
				) {
				struct_t < value_t > res;

				for (int i = 0; i < struct_t < value_t >::size; ++i) {
					res.data [i] = blend < value_t > (t, start.data [i], cp1.data [i], cp2.data [i], end.data [i]);
				}

				return res;
			}

			inline virtual void update (real t, property < target_value_t > * target) override {
				(*target) = blend (t, _start, _cp1, _cp2, _end);
			}

		};

	}
}

#endif