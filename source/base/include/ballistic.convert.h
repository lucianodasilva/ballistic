#pragma once
#ifndef _ballistic_convert_h_
#define _ballistic_convert_h_

#include <string>
#include <sstream>
#include <type_traits>

namespace ballistic {

#	define MSG_NOT_FUNDAMENTAL_SRC	"Non fundamental source type for conversion."
#	define MSG_NOT_FUNDAMENTAL_DST	"Non fundamental destination type for conversion."
#	define MSG_STRING_CONV_FAILED	"Conversion from string failed."

	template < class src_t, class dst_t > 
	inline void convert ( src_t & src, dst_t & dst ){
		// Compile time type conversion errors
		static_assert ( std::is_fundamental < src_t >::value, MSG_NOT_FUNDAMENTAL_SRC );
		static_assert ( std::is_fundamental < dst_t >::value, MSG_NOT_FUNDAMENTAL_DST );

		dst = (dst_t)src;
	}

	// Same type
	template < class t >
	inline void convert ( const t & src, t & dst ) {
		dst = src;
	}

	// Support for strings
	template < class string_t, class dst_t > 
	inline void __convert_string ( const string_t & src, dst_t & dst ) {
		// Compile time type conversion errors
		static_assert ( std::is_fundamental < dst_t >::value, MSG_NOT_FUNDAMENTAL_DST );

		std::stringstream stream (src);

		//extract whitespaces
		stream >> std::ws >> dst;
		if (stream.fail ()) {
			throw MSG_STRING_CONV_FAILED;
		}
	}

	template < class dst_t > 
	inline void convert ( const char * src, dst_t & dst ) {
		__convert_string < const char *, dst_t > ( src, dst );
	}

	template  < class dst_t >
	inline void convert ( std::string & src, dst_t & dst ) {
		__convert_string < std::string, dst_t > ( src, dst );
	}

	template < class dst_t >
	inline void convert ( const std::string & src, dst_t & dst ) {
		__convert_string < std::string, dst_t > ( src, dst );
	}

	template < class src_t >
	inline void convert ( src_t & src, std::string & dst ) {
		// Compile time type conversion errors
		static_assert ( std::is_fundamental < src_t >::value, MSG_NOT_FUNDAMENTAL_SRC );
		dst = std::to_string (src);
	}

	inline void convert ( std::string & src, std::string & dst ) {
		dst = src;
	}

	template < class dst_t, class src_t >
	inline dst_t convert_to ( src_t & src ) {
		dst_t tmp_value;
		convert (src, tmp_value);
		return tmp_value;
	}

}

#endif