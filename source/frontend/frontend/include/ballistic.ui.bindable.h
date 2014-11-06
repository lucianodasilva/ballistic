#ifndef _ballistic_ui_bindable_h_
#define _ballistic_ui_bindable_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace ui {

		template < class _t >
		struct bindable {
		private:
			

			struct iref {
				virtual const _t &  get () const = 0;
				virtual iref * clone () const = 0;
			};

			struct value_ref : public iref {
				_t value;
				inline value_ref (const _t & v) : value (v) {}
				inline virtual const _t & get () const { return value; }
				inline virtual iref * clone () const { return new value_ref (value); }
			};

			template < class _lambda_t >
			struct lambda_ref : public iref {
				_lambda_t instance;
				inline lambda_ref (const _lambda_t & v) : instance (v) {}
				inline virtual const _t & get () const { return instance (); }
				inline virtual iref * clone () const { return new lambda_ref < _lambda_t > (instance); }
			};

			template < class _value_t = _t, bool is_same_type = std::is_same < _t, _value_t >::value >
			struct reference {
				inline static iref * create () {
					return new value_ref (_t ());
				}

				inline static iref * create (const _t & v) {
					return new value_ref (v);
				}
			};

			template < class _value_t >
			struct reference < _value_t, false > {
				inline static iref * create (const _value_t & v) {
					return new lambda_ref < _value_t > (v);
				}
			};

			iref * _ref;

		public:

			~bindable () {
				delete _ref;
			}

			inline bindable () : _ref (reference <>::create ()) {}

			inline bindable (const bindable & v) : _ref (v._ref->clone ()) {}

			template < class _value_t >
			inline bindable (const _value_t & v) : _ref (reference < _value_t >::create (v)) {}

			inline void operator = (const bindable & v) {
				delete _ref;
				_ref = v._ref->clone ();
			}

			template < class _value_t >
			inline void operator = (const _value_t & v) {
				delete _ref;
				_ref = reference < _value_t >::create (v);
			}

			inline operator _t () const {
				return _ref->get ();
			}

		};

	}
}

#endif