// var_math.cpp : Defines the entry point for the console application.
//


#pragma warning (disable : 4996)

#include "stdafx.h"
#include <cinttypes>
#include <string>
#include <iostream>

#include <vector>

#include <smmintrin.h>

#include "calc_time.h"

	namespace math {

		template < class value_t >
		struct mat4_t {

			typedef mat4_t < value_t > this_type;

			static const uint32_t size = 16;
			static const uint32_t squared_dim = 4;

			union {
				value_t data [size];
				value_t data_sqr [squared_dim] [squared_dim];

				struct {
					value_t m00, m01, m02, m03;
					value_t m04, m05, m06, m07;
					value_t m08, m09, m10, m11;
					value_t m12, m13, m14, m15;
				};
			};

			inline mat4_t () :
				m00 (value_t(1)), m01 (value_t(0)), m02 (value_t(0)), m03 (value_t(0)),
				m04 (value_t(0)), m05 (value_t(1)), m06 (value_t(0)), m07 (value_t(0)),
				m08 (value_t(0)), m09 (value_t(0)), m10 (value_t(1)), m11 (value_t(0)),
				m12 (value_t(0)), m13 (value_t(0)), m14 (value_t(0)), m15 (value_t(1))

			{}

			inline mat4_t (this_type && v) {
				std::copy (std::begin (v.data), std::end (v.data), +data);
			}

			inline mat4_t (const this_type & v) {
				std::copy (std::begin (v.data), std::end (v.data), +data);
			}

			inline this_type & operator = (this_type && v) {
				std::copy (std::begin (v.data), std::end (v.data), +data);
				return *this;
			}

			inline this_type & operator = (const this_type & v) {
				std::copy (std::begin (v.data), std::end (v.data), +data);
				return *this;
			}

			inline this_type operator * (const value_t & v) const {
				this_type ret;

				for (int i = 0; i < size; ++i)
					ret.data [i] = data [i] * v;

				return ret;
			}

			inline this_type operator * (const this_type & v) const {
				//this_type ret;
				//
				//for (int i = 0; i < squared_dim; ++i) {
				//	for (int j = 0; j < squared_dim; ++j) {
				//		ret.data_sqr [i] [j] = value_t ();
				//		for (int k = 0; k < squared_dim; ++k)
				//			ret.data_sqr [i] [j] += (data_sqr [i] [k] * v.data_sqr [k] [j]);
				//	}
				//}
				//
				//return ret;

				this_type ret;
				int i, j, k;

				for (i = 0; i < squared_dim; ++i) {
					for (j = 0; j < squared_dim; ++j) {
						for (k = 0; k < squared_dim; ++k) {
							ret.data [squared_dim * i + k] += data [squared_dim * i + j] * v.data [squared_dim * j + k];
						}
					}
				}

				return ret;
			}

			inline this_type operator + (const this_type & v) const {
				this_type ret;

				for (int i = 0; i < size; ++i)
					ret.data [i] = data [i] + v.data [i];

				return ret;
			}

		};

	template < class value_t >
	struct mat4_t_nv {

		typedef mat4_t_nv < value_t > this_type;

		static const uint32_t size = 16;
		static const uint32_t squared_dim = 4;

		union {
			value_t data [size];
			value_t data_sqr [squared_dim] [squared_dim];

			struct {
				value_t m00, m01, m02, m03;
				value_t m04, m05, m06, m07;
				value_t m08, m09, m10, m11;
				value_t m12, m13, m14, m15;
			};
		};

		inline mat4_t_nv () :
			m00 (value_t(1)), m01 (value_t(0)), m02 (value_t(0)), m03 (value_t(0)),
			m04 (value_t(0)), m05 (value_t(1)), m06 (value_t(0)), m07 (value_t(0)),
			m08 (value_t(0)), m09 (value_t(0)), m10 (value_t(1)), m11 (value_t(0)),
			m12 (value_t(0)), m13 (value_t(0)), m14 (value_t(0)), m15 (value_t(1))

		{}

		inline mat4_t_nv (this_type && v) {
			std::copy (std::begin (v.data), std::end (v.data), +data);
		}

		inline mat4_t_nv (const this_type & v) {
			std::copy (std::begin (v.data), std::end (v.data), +data);
		}

		inline this_type & operator = (this_type && v) {
			std::copy (std::begin (v.data), std::end (v.data), +data);
			return *this;
		}

		inline this_type & operator = (const this_type & v) {
			std::copy (std::begin (v.data), std::end (v.data), +data);
			return *this;
		}

		inline this_type operator * (const value_t & v) const {
			this_type ret;

#pragma loop (no_vector)
			for (int i = 0; i < size; ++i)
				ret.data [i] = data [i] * v;

			return ret;
		}

		inline this_type operator * (const this_type & v) const {
			this_type ret;

#pragma loop (no_vector)
			for (int i = 0; i < squared_dim; ++i) {
#pragma loop (no_vector)
				for (int j = 0; j < squared_dim; ++j) {
					ret.data_sqr [i] [j] = value_t ();
#pragma loop (no_vector)
					for (int k = 0; k < squared_dim; ++k)
						ret.data_sqr [i] [j] += (data_sqr [i] [k] * v.data_sqr [k] [j]);
				}
			}

			return ret;
		}

		inline this_type operator + (const this_type & v) const {
			this_type ret;

#pragma loop (no_vector)
			for (int i = 0; i < size; ++i)
				ret.data [i] = data [i] + v.data [i];

			return ret;
		}

	};

	}

	using mat4_v = math::mat4_t < float >;
	using mat4_nv = math::mat4_t_nv < float > ;


#define MAX_TURNS 100000

//#pragma optimize ("", off)
void calculate_A () {

	mat4_v
		x,
		y,
		z;

	for (int i = 0; i < MAX_TURNS; ++i) {
		z = x * y;
		z = z + x;
	}
}

void test_a () { 
	calculate_A ();
}

void calculate_B () {

	mat4_nv x, y, z;

	for (int i = 0; i < MAX_TURNS; ++i) {
		z = x * y;
		z = z + x;
	}
}

void test_b () {
	calculate_B ();
}

//#pragma optimize ("", on)


int _tmain(int argc, _TCHAR* argv[])
{

	double seconds = diag::timed_avg_call (100, test_a) ();
	std::cout << std::endl << "auto vectorizer average: " << seconds << std::endl;

	seconds = diag::timed_avg_call (100, test_b) ();
	std::cout << std::endl << "no auto vectorizer average: " << seconds;

	std::cin >> seconds;

	return 0;
}

