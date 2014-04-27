#ifndef _ballistic_animation_function_type_h_
#define _ballistic_animation_function_type_h_

#include "ballistic.animation.function.h"
#include "ballistic.config.h"
#include "ballistic.iresource.h"


namespace ballistic {
	namespace animation {

		namespace details {

			template < class T >
			struct function_has_requirements {
			private:
				typedef char one;
				typedef long two;

				template < class C > static inline one test (decltype (C::require_parameters));
				template < class C > static inline two test (...);
			public:
				enum { value = sizeof (test <T> (0)) == sizeof (char) };
			};

			template < class T, bool has_requirements = function_has_requirements < T >::value >
			struct function_require_properties {
				inline static void require (containers::property_container & parameters) {
					T::require_parameters (parameters);
				}
			};

			template < class T >
			struct function_require_properties < T, false > {
				inline static void require (containers::property_container & parameters) {}
			};

		}

		class ifunction_type : public iresource {
		public:

			ifunction_type (const id_t & id);

			virtual ~ifunction_type ();

			virtual void require_parameters (containers::property_container & parameters) = 0;

			virtual ifunction * create (containers::property_container & parameters) = 0;
		};

		template < class function_t >
		class function_type : public ifunction_type {
			static_assert (is_base_of < ifunction, function_t >::value, "animation function type can only refer to classes derived from ifunction");
		public:

			inline function_type (const id_t & id) : ifunction_type (id) {}

			virtual void require_parameters (containers::property_container & parameters) {
				details::function_require_properties < function_t >::require (parameters);
			}

			virtual ifunction * create (containers::property_container & parameters) {
				ifunction * new_func = new function_t ();
				new_func->setup (parameters);
				return new_func;
			}

		};

	}
}

#endif