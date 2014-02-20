#pragma once
#ifndef _ballistic_var_h
#define _ballistic_var_h_

#include "ballistic.config.h"
#include "ballistic.id.h"
#include "ballistic.math.vecn_t.h"
#include "ballistic.math.matrixes.h"
#include "ballistic.text.h"

struct var {

	union {
		size_t		v_id;
		int32_t		v_int32;
		uint32_t	v_uint32;
		real		v_real;
		bool		v_bool;
		real		vector_data [16]; // matrix4 size
		char		text_data [sizeof (real)* 16]; // text size
	} data;
	
	inline var () {}
	
	inline var (var && v) : data (v.data) {}
	
	inline var (const var & v) : data (v.data) {}
	
	template < class T >
	inline var ( const T & v ) { set < T > (v); }
	
	inline var & operator = (var && v) {
		data = v.data;
		return *this;
	}
	
	inline var & operator = (var v ) {
		data = v.data;
		return *this;
	}

	template < class value_t, class data_t >
	inline void set (const ballistic::math::vecn_t < value_t, data_t > & v) {
		std::copy (
			std::begin (v.data),
			std::end (v.data),
			+data.vector_data
		);
	}

	template < class value_t >
	inline void set (const ballistic::math::mat4_t < value_t > & v) {
		std::copy (
			std::begin (v.data),
			std::end (v.data),
			+data.vector_data
		);
	}

	inline void set (const ballistic::text & v) {
		std::copy (
			std::begin (v.data),
			std::end (v.data),
			+data.text_data
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

//	inline void set (ballistic::id_t v) {
//		data.v_id = v;
//	}

	template < class T >
	inline T & as () {
		return *reinterpret_cast <T *> (+data.vector_data);
	}

	inline operator int32_t () const {
		return data.v_int32;
	}

	inline operator uint32_t () const {
		return data.v_uint32;
	}

	inline operator real () const {
		return data.v_real;
	}

	inline operator bool () const {
		return data.v_bool;
	}

//	inline operator ballistic::id_t () const {
//		return data.v_id;
//	}

	inline operator ballistic::text () const {
		return *reinterpret_cast <const ballistic::text *>(+data.text_data);
	}

	template < class T >
	inline operator ballistic::math::mat4_t < T > () const {
		return *reinterpret_cast <const ballistic::math::mat4_t < T > *>(+data.vector_data);
	}

	template < class T, class data_t >
	inline operator ballistic::math::vecn_t < T, data_t > () const {
		return *reinterpret_cast <const ballistic::math::vecn_t < T, data_t > *>(+data.vector_data);
	}

	// copy other stuffs
	template < class T >
	inline var & operator = (const T & v) {
		set (v);
		return *this;
	}

};

#endif
