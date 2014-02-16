#ifndef	_ballistic_text_h_
#define _ballistic_text_h_

#include "ballistic.debug.h"
#include "ballistic.config.h"

#include <memory>
#include <string>

#ifdef BALLISTIC_COMPILER_MSVC
#	pragma warning ( push )
#	pragma warning (disable : 4996)
#endif

namespace ballistic {

	struct text {
	public:
		static const uint32_t max_length = sizeof (real)* 16 - (sizeof (uint32_t) + 1); // matrix4 size - length - zero termination
	private:
		char _data [max_length + 1];
		uint32_t _length;
	public:

		inline void swap (text & v) { std::swap (_data, v._data); }

		inline text () : _length (0) { _data [0] = '\0'; }

		inline text (const text & v) : _length (v._length) {
			std::copy (+v._data, _length + v._data, +_data);
		}

		inline text & operator = (text v) {
			swap (v);
			return *this;
		}

		// convert from const char *
		inline text (const char * v) {
			_length = std::strlen (v);

			if (_length > max_length) {
				_length = max_length;
				debug_print ("[ballistic::text::char_ptr_ctor] text length is unsupported. Text will be trimmed.");
			}

			std::copy (v, v + _length, +_data);
			_data [_length]= '\0';
		}

		// convert from string
		inline text (const std::string & v) {
			_length = v.length ();

			if (_length > max_length) {
				_length = max_length;
				debug_print ("[ballistic::text::string_ctor] text length is unsupported. Text will be trimmed.");
			}

			v.copy (+_data, _length);
			_data [_length] = '\0';
		}

		inline operator std::string () {
			return std::string (+_data, _length);
		}

	};

}

#ifdef BALLISTIC_COMPILER_MSVC
#	pragma warning ( pop )
#endif

#endif