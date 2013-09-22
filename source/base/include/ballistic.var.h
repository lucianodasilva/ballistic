#pragma once
#ifndef _ballistic_var_h
#define _ballistic_var_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"
#include "ballistic.common_id.h"

#include "ballistic.debug.h"

#include "ballistic.math.h"
#include "ballistic.math.matrixes.h"

#include <string>
using namespace std;

#define declare_set(type) \
	inline void set (const type & v) { \
		clean_mem (); \
		_data.type##_v = v; _type = var_type_##type; \
	}

#define declare_set_struct(type) \
	inline void set (const type & v) { \
		clean_mem (); \
		_data.ptr_v = (void *)new type (v); _type = var_type_##type; \
	}

#define delete_switch(type) \
	case (var_type_##type): \
	delete (type *)_data.ptr_v; \
	break;

#define convert_switch(type) \
	case (var_type_##type): \
	ballistic::convert (_data.type##_v, v); \
		break;

#define declare_get(type) \
inline void get (type & v) const { \
	if (_type == var_type_string) { \
		ballistic::convert (*(string *)_data.ptr_v, v); \
		return; \
	} \
	if (_type & var_type_struct) { \
		debug_warn ("[ballistic::var::get(" #type ")] Cannot convert struct to " #type ". Value set to zero."); \
		return; \
	} \
	switch (_type) { \
		convert_switch (int32);	\
		convert_switch (uint32); \
		convert_switch (double); \
		convert_switch (bool); \
	default: \
		debug_warn ("[ballistic::var::get(" #type ")] Unknown data type. Value converted as empty."); \
		v = type (); \
	} \
}

#define declare_get_struct(type) \
	inline void get (type & v) const { \
		if (_type == var_type_string) { \
		\
			ballistic::convert_vectors (*(string *)_data.ptr_v, v); \
			return; \
		} \
		\
		if (_type != var_type_##type) { \
			debug_warn ("[ballistic::var::get(" #type ")] Unknown data type. Value converted as empty."); \
			v = type (); \
			return;	\
		} \
		v = *(type *)_data.ptr_v; \
	}

class var {
public:

	enum var_type {
		var_type_none	= 0,
		var_type_bool	= 1,
		var_type_int32	= 2,
		var_type_uint32 = 4,
		var_type_double	= 8,
		var_type_struct = 128,
		var_type_string = var_type_struct + 1,
		var_type_vec2	= var_type_struct + 2,
		var_type_vec3	= var_type_struct + 4,
		var_type_vec4	= var_type_struct + 8,
		var_type_mat4	= var_type_struct + 16
	};

private:

	var_type _type;
	
	union var_data {
		bool	bool_v;
		int32	int32_v;
		uint32	uint32_v;
		double	double_v;
		void *	ptr_v;
	} _data;

	inline void clean_mem () {
		if (!(_type & var_type_struct))
			return;

		switch (_type) {
			delete_switch (string);
			delete_switch (vec2);
			delete_switch (vec3);
			delete_switch (vec4);
			delete_switch (mat4);
		default:
			debug_warn ("[ballistic::var::clean_mem] Unknownw data type. No data deleted.");
		}
	}

	inline void copy_mem (const var & v) {
		_type = v._type;

		if (_type & var_type_struct) {
			switch (_type) {
			case (var_type_vec2) :
				_data.ptr_v = new vec2 (*(vec2 *)v._data.ptr_v);
				break;
			case (var_type_vec3) :
				_data.ptr_v = new vec3 (*(vec3 *)v._data.ptr_v);
				break;
			case (var_type_vec4) :
				_data.ptr_v = new vec4 (*(vec4 *)v._data.ptr_v);
				break;
			case (var_type_mat4) :
				_data.ptr_v = new mat4 (*(mat4 *)v._data.ptr_v);
				break;
			case (var_type_string) :
				_data.ptr_v = new string (*(string *)v._data.ptr_v);
				break;
			default:
				debug_error ("[ballistic::var::copy_mem] Unknown type found. No var set to null.");
				_type = var_type_none;
				break;
			}
		} else
			_data = v._data;
	}

public:

	inline static void swap (var & v1, var & v2) {
		var_type t_type = v1._type;
		var_data t_data = v1._data;

		v1._type = v2._type;
		v1._data = v2._data;

		v2._type = t_type;
		v2._data = t_data;
	}

	// details

	declare_set (int32)
	declare_set (uint32)
	declare_set (double)
	declare_set (bool)
	
	declare_set_struct (string)
	declare_set_struct (vec2)
	declare_set_struct (vec3)
	declare_set_struct (vec4)
	declare_set_struct (mat4)

	declare_get (int32)
	declare_get (uint32)
	declare_get (double)
	declare_get (bool)

	declare_get_struct (vec2)
	declare_get_struct (vec3)
	declare_get_struct (vec4)
	declare_get_struct (mat4)

#ifdef BALLISTIC_DEBUG

	inline void get (ballistic::id_t & v) const {
		get (v.key);
	}

	inline void set (const ballistic::id_t & v) {
		set (v.key);
	}

#endif

	inline void get (string & v) const {

		if (_type == var_type_string) {
			v = *(string *)_data.ptr_v;
			return;
		}

		switch (_type) {
		case (var_type_int32) :
			ballistic::convert (_data.int32_v, v);
			break;
		case (var_type_uint32) :
			ballistic::convert (_data.uint32_v, v);
			break;
		case (var_type_double) :
			ballistic::convert (_data.double_v, v);
			break;
		case (var_type_bool) :
			ballistic::convert (_data.bool_v, v);
			break;
		case (var_type_vec2) :
			ballistic::convert_vectors (*(vec2 *)_data.ptr_v, v);
			break;
		case (var_type_vec3) :
			ballistic::convert_vectors (*(vec3 *)_data.ptr_v, v);
			break;
		case (var_type_vec4) :
			ballistic::convert_vectors (*(vec4 *)_data.ptr_v, v);
			break;
		default:
			debug_error ("[ballistic::var::get(string)] Cannot convert type to string. Value converted as empty.");
		}
	}

	// external fixtures

	inline var () : _type (var_type_none) {}

	inline var (const var & v) : _type (var_type_none) {
		copy_mem (v);
	}

	inline var (var && v) : _type (var_type_none) {
		swap (*this, v);
	}

	template < class T >
	inline var (const T & v) : _type (var_type_none) { 
		static_assert (!std::is_pointer <T>::value, "[ballistic::var::ctor] Variant does not support pointers");
		set (v);	
	}

	virtual ~var () { 
		clean_mem (); 
	}

	template < class T >
	inline var & operator = (const T & v) {
		static_assert (!std::is_pointer <T>::value, "[ballistic::var::ctor] Variant does not support pointers");
		set (v);
		return *this;
	}

	inline var & operator = (var v) {
		swap (*this, v);
		return *this;
	}

	template < class T >
	T as () const {
		T v;
		get (v);
		return v;
	}

};




#endif

//#pragma once
//#ifndef _ballistic_var_h_
//#define _ballistic_var_h_
//
//#include "ballistic.config.h"
//#include "ballistic.convert.h"
//#include "ballistic.debug.h"
//
//#include <string>
//#include <type_traits>
//
//#define MSG_CANNOT_CONVERT_TO_STRUCT "Variant cannot convert objects to fundamental types."
//#define MSG_CANNOT_CONVERT_TO_POINTER "Variant cannot convert pointer to fundamental types."
//
//#define MSG_CANNOT_CONVERT_FROM_STRUCT "Variant cannot convert from struct to other types."
//#define MSG_CANNOT_CONVERT_FROM_POINTER "Variant cannot convert from pointer to other types."
//
//#define MSG_CANNOT_CONTAIN_ARRAYS "Variant type does not support arrays."
//
//class var {
//private:
//	
//	enum var_type : unsigned int{
//		var_type_none		= 0,
//		var_type_int		= 1,
//		var_type_uint		= 2,
//		var_type_double		= 4,
//		var_type_bool		= 8,
//		var_type_pointer	= 16,
//		var_type_struct		= 32,
//		var_type_string		= 64 + 32 // string specialization ( struct + string )
//	};
//	
//	struct _i_var_box {
//		virtual ~_i_var_box () {}
//		
//		virtual void * get_data () = 0;
//		virtual _i_var_box * copy () = 0;
//
//	};
//	
//	template < class t >
//	struct _var_box : public _i_var_box {
//		
//		typedef typename std::conditional <
//			std::is_pointer < t >::value,
//			typename std::remove_pointer < typename std::decay < t >::type >::type,
//			typename std::decay < t >::type
//		>::type simple_t;
//		
//		t _value;
//		
//		inline _var_box ( const t & val ) : _value ( val ){}
//		
//		inline static void * get_data ( simple_t & value ) { return (void *)&value; }
//		
//		inline static void * get_data ( simple_t * value ) { return (void *)value; }
//		
//		inline virtual void * get_data () override { return get_data (_value); }
//
//		inline virtual _i_var_box * copy () override {
//			return new _var_box < t > ( _value );
//		}
//			
//	};
//	
//	union {
//		int32	_int_v;
//		uint32	_uint_v;
//		double	_double_v;
//		bool	_bool_v;
//	
//		_i_var_box * _box_v;
//		
//	} _data;
//	
//	var_type _type;
//	
//	template < class t >
//	struct _setter_pointer {
//		inline static void set ( var & var_ref, const t & val ) {
//			if (val == nullptr) {
//				var_ref._data._box_v = nullptr;
//				var_ref._type = var_type_none;
//				return;
//			}
//			
//			var_ref._data._box_v = new _var_box < t > (val);
//			var_ref._type = var_type_pointer;
//		}
//	};
//
//	template < class t >
//	struct _setter_struct {
//		inline static void set ( var & var_ref, const t & val ) {
//			var_ref._data._box_v = new _var_box < t > ( val );
//
//			if (std::is_same < t, std::string >::value)
//				var_ref._type = var_type_string;
//			else
//				var_ref._type = var_type_struct;
//		}
//	};
//	
//	template < class t >
//	struct _setter_int {
//		inline static void set ( var & var_ref, const t & val ) {
//			ballistic::convert ( val, var_ref._data._int_v );
//			var_ref._type = var_type_int;
//		}
//	};
//	
//	template < class t >
//	struct _setter_uint {
//		inline static void set ( var & var_ref, const t & val ) {
//			ballistic::convert ( val, var_ref._data._uint_v );
//			var_ref._type = var_type_uint;
//		}
//	};
//
//	template < class t >
//	struct _setter_double {
//		inline static void set ( var & var_ref, const t & val ) {
//			ballistic::convert ( val, var_ref._data._double_v );
//			var_ref._type = var_type_double;
//		}
//	};
//
//	template < class t >
//	struct _setter_bool {
//		inline static void set (var & var_ref, const t & val) {
//			ballistic::convert (val, var_ref._data._bool_v);
//			var_ref._type = var_type_bool;
//		}
//	};
//
//	template  < class t >
//	struct _getter_fundamental {
//		inline static void get ( const var & var_ref, t & val ) {
//			switch ( var_ref._type ) {
//				case (var_type_none):
//					//val = 0;
//					break;
//				case (var_type_int):
//					ballistic::convert ( var_ref._data._int_v, val );
//					break;
//				case (var_type_uint):
//					ballistic::convert ( var_ref._data._uint_v, val);
//					break;
//				case (var_type_double):
//					ballistic::convert ( var_ref._data._double_v, val );
//					break;
//				case (var_type_bool) :
//					ballistic::convert (var_ref._data._bool_v, val);
//					break;
//				case (var_type_string):
//					{
//						std::string * ptr = static_cast < std::string * > ( var_ref._data._box_v->get_data () );
//						ballistic::convert ( *ptr, val );
//					}
//					break;
//				case (var_type_struct):
//					debug_error ("[ballistic::var::get] " << MSG_CANNOT_CONVERT_TO_STRUCT);
//					break;
//				case (var_type_pointer):
//					debug_error ("[ballistic::var::get] " << MSG_CANNOT_CONVERT_TO_POINTER);
//					break;
//			}
//		}
//	};
//
//	template < class t >
//	struct _getter_pointer {
//		inline static void get ( const var & var_ref, t & val ) {
//			if ( var_ref._type == var_type_none ) {
//				val = nullptr;
//				return;
//			}
//
//			if ( var_ref._type != var_type_pointer )
//				debug_error ("[ballistic::var::get] " << MSG_CANNOT_CONVERT_FROM_POINTER);
//
//			val = static_cast < t > ( var_ref._data._box_v->get_data () );
//		}
//	};
//
//	template < class t >
//	struct _getter_struct {
//		inline static void get ( const var & var_ref, t & val ) {
//			if (var_ref._type == var_type_none) {
//				val = t ();
//				return;
//			}
//
//			if (var_ref._type != var_type_struct)
//				debug_error ("[ballistic::var::get] " << MSG_CANNOT_CONVERT_FROM_STRUCT);
//
//			t * ptr = static_cast < t * > ( var_ref._data._box_v->get_data () );
//			val = *ptr;
//		}
//	};
//	
//	template < class t >
//	struct _var_handler {
//		
//		typedef typename std::conditional <
//			std::is_fundamental < t >::value,
//			typename std::conditional <
//				std::is_integral < t >::value,
//				typename std::conditional <
//					std::is_signed< t >::value,
//					typename std::conditional < 
//						std::is_same < t, bool >::value,
//						_setter_bool < t >,
//						_setter_int < t >
//					>::type,
//					_setter_uint < t >
//				>::type,
//				_setter_double < t >
//			>::type,
//			typename std::conditional <
//				std::is_pointer < t >::value,
//				_setter_pointer < t >,
//				_setter_struct < t >
//			>::type
//		>::type _setter_t;
//
//		typedef typename std::conditional <
//			std::is_fundamental < t >::value,
//			_getter_fundamental < t >,
//			typename std::conditional <
//				std::is_pointer < t >::value,
//				_getter_pointer < t >,
//				typename std::conditional < 
//					std::is_same < t, std::string >::value,
//						_getter_fundamental < t >,
//						_getter_struct < t >
//				>::type
//			>::type
//		>::type _getter_t;
//		
//		inline static void set ( var & var_ref, const t & val ) {
//			static_assert ( !std::is_array < t >::value, MSG_CANNOT_CONTAIN_ARRAYS );
//			
//			if (var_ref._type == var_type_pointer || 
//				var_ref._type == var_type_struct || 
//				var_ref._type == var_type_string )
//			{
//				delete var_ref._data._box_v;
//			}
//				
//			_setter_t::set ( var_ref, val );
//			
//		}
//		
//		inline static void get ( const var & var_ref, t & val ) {
//			static_assert ( !std::is_array < t >::value, MSG_CANNOT_CONTAIN_ARRAYS );
//			
//			_getter_t::get ( var_ref, val );
//		}
//		
//	};
//	
//public:
//	
//	// null setters
//	inline var () : _type ( var_type_none ) {}
//
//	inline var ( const std::nullptr_t & origin ) : _type ( var_type_none) {}
//	
//	virtual ~var() {
//		if (_type == var_type_string ||
//			_type == var_type_struct ||
//			_type == var_type_pointer
//		)
//			delete _data._box_v;
//	}
//
//	// copy 
//	inline var ( const var & origin ) :
//		_data ( origin._data ),
//		_type ( origin._type )
//	{
//		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer )
//			_data._box_v = origin._data._box_v->copy ();
//	}
//
//	inline var operator = ( const var & origin ) {
//		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer)
//			delete _data._box_v;
//
//		_data = origin._data;
//		_type = origin._type;
//
//		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer )
//			_data._box_v = origin._data._box_v->copy ();
//		
//		return origin;
//	}
//
//	// value setters
//	template < class t >
//	inline var ( const t & origin ) : _type (var_type_none) {
//		_var_handler < t >::set ( *this, origin );
//	}
//	
//	template < class t >
//	inline t operator = ( const t & val ) {
//		_var_handler < t >::set ( *this, val );
//		return val;
//	}
//	
//	// value getters
//	template < class t >
//	inline t as () const {
//		t val;
//		_var_handler < t >::get ( *this, val );
//		return val;
//	}
//
//	template < class t >
//	inline operator t () const {
//		return as < t >();
//	}
//
//	// string specialization
//	inline var ( const char * origin ) {
//		_var_handler < std::string >::set ( *this, std::string ( origin ) );
//	}
//
//	inline const char * operator = ( const char * val ) {
//		_var_handler < std::string >::set ( *this, std::string ( val ) );
//		return val;
//	}
//	
//};
//
//#undef MSG_CANNOT_CONVERT_TO_STRUCT
//#undef MSG_CANNOT_CONVERT_TO_POINTER
//
//#undef MSG_CANNOT_CONVERT_FROM_STRUCT
//#undef MSG_CANNOT_CONVERT_FROM_POINTER
//
//#undef MSG_CANNOT_CONTAIN_ARRAYS
//
//#endif
