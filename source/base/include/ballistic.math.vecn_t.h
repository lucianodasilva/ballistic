#ifndef _ballistic_vector_data_h_
#define _ballistic_vector_data_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include <memory>
#include <initializer_list>

namespace ballistic {
	namespace math {

		template < class value_t, class data_t >
		struct vecn_t : public data_t {

			typedef vecn_t < value_t, data_t > this_type;

			inline vecn_t () : data_t () {}

			inline vecn_t (const std::initializer_list < value_t > & init ) {
				if (init.size () != data_t::size) {
					debug_print ("[vecn_t::init_list_ctor] init list size invalid for used vector type");
					return;
				}
				std::copy (init.begin (), init.end (), +data_t::data);
			}

			inline vecn_t ( this_type && v ) {
				std::copy (std::begin (v.data), std::end (v.data), +data_t::data);
			}
			
			inline vecn_t ( const this_type & v ) {
				std::copy (std::begin (v.data), std::end (v.data), +data_t::data);
			}

			inline this_type & operator = ( this_type && v ) {
				std::copy (std::begin (v.data), std::end (v.data), +data_t::data);
				return *this;
			}
			
			inline this_type & operator = ( const this_type & v ) {
				std::copy (std::begin (v.data), std::end (v.data), +data_t::data);
				return *this;
			}

		};

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator + ( const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2 ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v1.data [i] + v2.data [i];

			return res;
		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator - ( const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2 ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v1.data [i] - v2.data [i];

			return res;
		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator * ( const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2 ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v1.data [i] * v2.data [i];

			return res;
		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator * ( const vecn_t < value_t, data_t > & v, real m ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v.data [i] * m;

			return res;

		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator / ( const vecn_t < value_t, data_t > & v1, const vecn_t < value_t, data_t > & v2 ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v1.data [i] / v2.data [i];

			return res;

		}

		template < class value_t, class data_t >
		inline vecn_t < value_t, data_t > operator / ( const vecn_t < value_t, data_t > & v, real d ) {
			vecn_t < value_t, data_t > res;

			for (int i = 0; i < data_t::size; ++i)
				res.data [i] = v.data [i] / d;

			return res;

		}

	}
}


#endif
