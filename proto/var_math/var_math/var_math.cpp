// var_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cinttypes>
#include <string>
#include <iostream>

#include <smmintrin.h>

#include "calc_time.h"

namespace math {

	template < int index, int length >
	struct for_op {

		template < class oper_t >
		inline static void run (oper_t & op) {
			op (index);
			for_op < index + 1, length >::run (op);
		}

	};

	template < int length >
	struct for_op < length, length > {

		template < class oper_t >
		inline static void run (oper_t & op) {}

	};

	template < class value_t, class data_t >
	struct vecn_t : public data_t {

		typedef vecn_t < value_t, data_t > this_type;

		inline void swap (this_type & right) {
			std::swap (data, right.data);
		}

		inline void clear () {
			for (value_t & v : this->data)
				v = value_t (); // zero
		}

		inline vecn_t () {
			clear ();
		}
		
		inline this_type & operator = (this_type v) {
			swap (v);
			return *this;
		}

	};

	template < class value_t, class data_t >
	inline vecn_t < value_t, data_t > operator * (
		const vecn_t < value_t, data_t > & va,
		float vb) {
		vecn_t r;

		for_op < 0, data_t::size >::run (
			[&](int i) {r.data [i] = va.data [i] * vb; }
		);

		return r;
	}

	template < class value_t, class data_t >
	inline vecn_t < value_t, data_t > operator * (
		const vecn_t < value_t, data_t > & v1, 
		const vecn_t < value_t, data_t > & v2) 
	{
		vecn_t < value_t, data_t > r;

		for_op < 0, data_t::size >::run (
			[&](int i) { r.data [i] = v1.data [i] * v2.data [i]; }
		);

		return r;
	}

	template < class value_t, class data_t >
	inline vecn_t < value_t, data_t > operator - (
		const vecn_t < value_t, data_t > & v1,
		const vecn_t < value_t, data_t > & v2) {
		vecn_t < value_t, data_t > r;

		for_op < 0, data_t::size >::run (
			[&](int i) { r.data [i] = v1.data [i] - v2.data [i]; }
		);

		return r;
	}

	template < class value_t >
	struct vec2_data {
		static const uint32_t size = 2;

		union {
			value_t data [size];
			struct {
				value_t x, y;
			};
		};
	};

	template < class value_t >
	using vec2_t = vecn_t < value_t, vec2_data < value_t > >;

	template< class value_t >
	struct vec4_data {

		static const uint32_t size = 4;

		union {
			value_t data [size];
			struct { value_t x, y, z, w; };
			struct { value_t r, g, b, a; };
		};
	};

	template < class value_t >
	using vec4_t = vecn_t < value_t, vec4_data < value_t > >;

	template < class value_t, class data_t >
	inline value_t dot (
		const vecn_t < value_t, data_t > & v1,
		const vecn_t < value_t, data_t > & v2
	) {
		static_assert (data_t::size >= 4, "Invalid vector size for dot product calculation!");
		value_t r = .000000000001F;
		
		for (int i = 0; i < data_t::size; ++i)
			r += v1.data [i] * v2.data [i];

		return r;
	}

	template < class value_t, class data_t, class this_type = vecn_t < value_t, data_t > >
	inline value_t sqr_length (const this_type & v) {
		return dot (v, v);
	}

	template < class value_t, class data_t, class this_type = vecn_t < value_t, data_t > >
	inline value_t sqr_length (const this_type & v1, const this_type & v2) {
		return sqr_lenght (v2 - v1);
	}

	template < class value_t, class data_t, class this_type = vecn_t < value_t, data_t > >
	inline value_t length (const this_type & v) {
		return sqrtf (sqr_length (v));
	}

	template < class value_t, class data_t, class this_type = vecn_t < value_t, data_t > >
	inline value_t length (const this_type & v1, const this_type & v2) {
		return sqrtf (sqr_length (v1, v2));
	}

}

#define MAX_TURNS 1000000

math::vec4_t < float > calculate_normal () {

	math::vec4_t < float > x, y, z;

	x.x = 10;
	y.x = 10;

	for (int i = 0; i < MAX_TURNS; ++i) {
		math::vec4_t < float > zr;
		math::for_op < 0, 4 >::run (
			[&](int j) {zr.data [j] = x.data [j] * y.data [j]; }
		);
		z = zr;
	}

	return z;

}

void test_normal () { 
	math::vec4_t < float > v = calculate_normal ();
	std::cout << v.x;
}

math::vec4_t < float > calculate_unfold () {

	math::vec4_t < float > x, y, z;

	x.x = 10;
	y.x = 10;

	for (int i = 0; i < MAX_TURNS; ++i)
		z = x * y;

	return z;
}

void test_unfold () { 
	auto v = calculate_unfold ();
	std::cout << v.x;
}

int _tmain(int argc, _TCHAR* argv[])
{

	double seconds = diag::timed_avg_call (100, test_normal) ();
	std::cout << std::endl << "Normal execution average: " << seconds << std::endl;

	seconds = diag::timed_avg_call (100, test_unfold) ();
	std::cout << std::endl << "Other execution average: " << seconds;

	std::cin >> seconds;

	math::vec4_t < float > v1;
	math::dot (v1, v1);

	return 0;
}

