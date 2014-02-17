// var_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cinttypes>
#include <string>
#include <iostream>

#include <smmintrin.h>

#include "calc_time.h"

namespace math {

	template < class value_t, size_t length >
	inline size_t array_size (value_t (&v) [length]) {
		return length;
	}

	template < class value_t, size_t length, size_t index >
	struct _unfold_vector_op {

		template < class op_t >
		inline static void calc (op_t op, value_t (&v1) [length], value_t (&v2) [length], value_t (&res) [length]) {
			op (v1 [index], v2 [index], res [index]);
			_unfold_vector_op < value_t, length, index - 1 >::calc (op, v1, v2, res);
		}

	};

	template < class value_t, size_t length>
	struct _unfold_vector_op < value_t, length, 0 > {

		template < class op_t >
		inline static void calc (op_t op, value_t (&v1) [length], value_t (&v2) [length], value_t (&res) [length]) {
			op (v1 [0], v2 [0], res [0]);
		}

	};

	template < class value_t, size_t length, class op_t >
	inline void unfold_vector_op (op_t op, value_t (&v1) [length], value_t (&v2) [length], value_t (&res) [length]) {
		_unfold_vector_op < value_t, length, length - 1>::calc (
			op,
			v1, v2, res
			);
	}

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

		math::unfold_vector_op (
			[](value_t & v1, value_t & v2, value_t & ret) { ret = v1 * v2; },
			data,

		);

		for (int i = 0; i < data_t::size; ++i)
			r.data [i] = va.data [i] * vb;

		return r;
	}

	template < class value_t, class data_t >
	inline vecn_t < value_t, data_t > operator * (
		const vecn_t < value_t, data_t > & v1, 
		const vecn_t < value_t, data_t > & v2) 
	{
		vecn_t < value_t, data_t > r;

		for (int i = 0; i < data_t::size; ++i)
			r.data [i] = v1.data [i] * v2.data [i];

		return r;
	}

	template < class value_t, class data_t >
	inline vecn_t < value_t, data_t > operator - (
		const vecn_t < value_t, data_t > & v1,
		const vecn_t < value_t, data_t > & v2) {
		vecn_t < value_t, data_t > r;

		for (int i = 0; i < data_t::size; ++i)
			r.data [i] = v1.data [i] - v2.data [i];

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

	for (int i = 0; i < MAX_TURNS; ++i)
		math::unfold_vector_op ([](float & a, float & b, float & c) { c = a * b; },
			x.data, y.data, z.data
		);

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

template < class T1, size_t s, class ... param_v >
size_t first_size (T1 (&v) [s], param_v...) {
	return s;
};

template < size_t index >
struct _unfold_operation {

	template < class oper_t, class ... param_v >
	inline static void exec (oper_t op, param_v ... params) {
		op (params [index] ...);
		_unfold_operation < index - 1 >::exec (op, params...);
	}

};

template < >
struct _unfold_operation < 0 > {

	template < class oper_t, class ... param_v >
	inline static void exec (oper_t op, param_v ... params) {
		op (params [0] ...);
	}

};

template < int iter, class oper_t, class ... param_v >
void unfold_operation ( oper_t op, param_v ... params ) {

	_unfold_operation < iter >::exec (op, params ...);
}

int _tmain(int argc, _TCHAR* argv[])
{

	float array_v [4] = {1, 2, 3, 4};
	float v = 12;

	unfold_operation < 12 > (
		[&](float & a) { a *= v; },
		array_v
		);


	double seconds = diag::timed_avg_call (100, test_normal) ();
	std::cout << std::endl << "Normal execution average: " << seconds << std::endl;

	seconds = diag::timed_avg_call (100, test_unfold) ();
	std::cout << std::endl << "Other execution average: " << seconds;

	std::cin >> seconds;

	math::vec4_t < float > v1;
	math::dot (v1, v1);

	return 0;
}

