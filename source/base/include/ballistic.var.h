#pragma once
#ifndef _ballistic_var_h
#define _ballistic_var_h_

#include "ballistic.config.h"
#include "ballistic.vector_data.h"

#ifdef BALLISTIC_COMPILER_MSVC
#	pragma warning ( push )
#	pragma warning (disable : 4996)
#endif

struct var_data {

	union {
		int32_t		v_int32;
		uint32_t	v_uint32;
		real		v_real;
		bool		v_bool;
		real		vector_data [16]; // matrix4 size
		char		text_data [sizeof (real) * 16]; // text size
	} data;

};

struct var {

	union {
		int32_t		v_int32;
		uint32_t	v_uint32;
		real		v_real;
		bool		v_bool;
		real		vector_data [16]; // matrix4 size
		char		text_data [sizeof (real)* 16]; // text size
	} data;

	inline void swap (var & v) {
		std::swap (data.vector_data, v.data.vector_data);
	}

	template < class v_t >
	inline void set (v_t & v) {
		copy (
			reinterpret_cast < real * >	(&v),
			+data.vector_data,
			sizeof (v_t) / 4
			);
	}

	inline void set (int32_t v) {
		data.v_int32 = v;
	}

	inline void set (uint32_t v) {
		data.v_uint32 = v;
	}

	inline void set (bool v) {
		data.v_bool = v;
	}

	inline void set (real v) {
		data.v_real = v;
	}

	inline var () {}

	inline var (const var & v) : data (v.data) {}

	template < class v_t >
	inline static var & from (v_t & v) {
		return *reinterpret_cast <var *>	(&v);
	}

	template < class v_t >
	inline v_t as () {
		return *reinterpret_cast <v_t *> (&data);
	}

	inline var & operator = (var v) {
		swap (v);
		return *this;
	}

	// copy other stuffs
	template < class v_t >
	inline var & operator = (v_t v) {
		set (v);
		return *this;
	}

};

#ifdef BALLISTIC_COMPILER_MSVC
#	pragma warning ( pop )
#endif

#endif
