#pragma once
#ifndef _ballistic_var_h_
#define _ballistic_var_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"

#include <string>
#include <type_traits>

#define MSG_CANNOT_CONVERT_TO_STRUCT "Variant cannot convert objects to fundamental types."
#define MSG_CANNOT_CONVERT_TO_POINTER "Variant cannot convert pointer to fundamental types."

#define MSG_CANNOT_CONVERT_FROM_STRUCT "Variant cannot convert from struct to other types."
#define MSG_CANNOT_CONVERT_FROM_POINTER "Variant cannot convert from pointer to other types."

#define MSG_CANNOT_CONTAIN_ARRAYS "Variant type does not support arrays."

class var {
private:
	
	enum var_type : unsigned int{
		var_type_none		= 0,
		var_type_int64		= 1,
		var_type_uint64		= 2,
		var_type_double		= 4,
		var_type_pointer	= 8,
		var_type_struct		= 16,
		var_type_string		= 48 // string specialization ( struct + string )
	};
	
	struct _i_var_box {
		virtual ~_i_var_box () {}
		
		virtual void * get_data () = 0;
		virtual _i_var_box * copy () = 0;

	};
	
	template < class t >
	struct _var_box : public _i_var_box {
		
		typedef typename std::conditional <
			std::is_pointer < t >::value,
			typename std::remove_pointer < typename std::decay < t >::type >::type,
			typename std::decay < t >::type
		>::type simple_t;
		
		t _value;
		
		inline _var_box ( const t & val ) : _value ( val ){}
		
		inline static void * get_data ( simple_t & value ) { return (void *)&value; }
		
		inline static void * get_data ( simple_t * value ) { return (void *)value; }
		
		inline virtual void * get_data () override { return get_data (_value); }

		inline virtual _i_var_box * copy () override {
			return new _var_box < t > ( _value );
		}
			
	};
	
	union {
		int64	_int64_v;
		uint64	_uint64_v;
		double	_double_v;
	
		_i_var_box * _box_v;
		
	} _data;
	
	var_type _type;
	
	template < class t >
	struct _setter_pointer {
		inline static void set ( var & var_ref, const t & val ) {
			if (val == nullptr) {
				var_ref._data._box_v = nullptr;
				var_ref._type = var_type_none;
				return;
			}
			
			var_ref._data._box_v = new _var_box < t > (val);
			var_ref._type = var_type_pointer;
		}
	};

	template < class t >
	struct _setter_struct {
		inline static void set ( var & var_ref, const t & val ) {
			var_ref._data._box_v = new _var_box < t > ( val );

			if (std::is_same < t, std::string >::value)
				var_ref._type = var_type_string;
			else
				var_ref._type = var_type_struct;
		}
	};
	
	template < class t >
	struct _setter_int {
		inline static void set ( var & var_ref, const t & val ) {
			ballistic::convert ( val, var_ref._data._int64_v );
			var_ref._type = var_type_int64;
		}
	};
	
	template < class t >
	struct _setter_uint {
		inline static void set ( var & var_ref, const t & val ) {
			ballistic::convert ( val, var_ref._data._uint64_v );
			var_ref._type = var_type_uint64;
		}
	};

	template < class t >
	struct _setter_double {
		inline static void set ( var & var_ref, const t & val ) {
			ballistic::convert ( val, var_ref._data._double_v );
			var_ref._type = var_type_double;
		}
	};

	template  < class t >
	struct _getter_fundamental {
		inline static void get ( const var & var_ref, t & val ) {
			switch ( var_ref._type ) {
				case (var_type_none):
					//val = 0;
					break;
				case (var_type_int64):
					ballistic::convert ( var_ref._data._int64_v, val );
					break;
				case (var_type_uint64):
					ballistic::convert ( var_ref._data._uint64_v, val);
					break;
				case (var_type_double):
					ballistic::convert ( var_ref._data._double_v, val );
					break;
				case (var_type_string):
					{
						std::string * ptr = static_cast < std::string * > ( var_ref._data._box_v->get_data () );
						ballistic::convert ( *ptr, val );
					}
					break;
				case (var_type_struct):
					throw MSG_CANNOT_CONVERT_TO_STRUCT;
					break;
				case (var_type_pointer):
					throw MSG_CANNOT_CONVERT_TO_POINTER;
					break;
			}
		}
	};

	template < class t >
	struct _getter_pointer {
		inline static void get ( const var & var_ref, t & val ) {
			if ( var_ref._type == var_type_none ) {
				val = nullptr;
				return;
			}

			if ( var_ref._type != var_type_pointer )
				throw MSG_CANNOT_CONVERT_FROM_POINTER;

			val = static_cast < t > ( var_ref._data._box_v->get_data () );
		}
	};

	template < class t >
	struct _getter_struct {
		inline static void get ( const var & var_ref, t & val ) {
			if (var_ref._type == var_type_none) {
				val = t ();
				return;
			}

			if ( var_ref._type != var_type_struct )
				throw MSG_CANNOT_CONVERT_FROM_STRUCT;

			t * ptr = static_cast < t * > ( var_ref._data._box_v->get_data () );
			val = *ptr;
		}
	};
	
	template < class t >
	struct _var_handler {
		
		typedef typename std::conditional <
			std::is_fundamental < t >::value,
				typename std::conditional <
					std::is_integral < t >::value,
						typename std::conditional <
							std::is_signed< t >::value,
								_setter_int < t >,
								_setter_uint < t >
						>::type,
						_setter_double < t >
				>::type,
				typename std::conditional <
					std::is_pointer < t >::value,
						_setter_pointer < t >,
						_setter_struct < t >
				>::type
		>::type _setter_t;

		typedef typename std::conditional <
			std::is_fundamental < t >::value,
			_getter_fundamental < t >,
			typename std::conditional <
				std::is_pointer < t >::value,
				_getter_pointer < t >,
				typename std::conditional < 
					std::is_same < t, std::string >::value,
						_getter_fundamental < t >,
						_getter_struct < t >
				>::type
			>::type
		>::type _getter_t;
		
		inline static void set ( var & var_ref, const t & val ) {
			static_assert ( !std::is_array < t >::value, MSG_CANNOT_CONTAIN_ARRAYS );
			
			if (var_ref._type == var_type_pointer || 
				var_ref._type == var_type_struct || 
				var_ref._type == var_type_string )
			{
				delete var_ref._data._box_v;
			}
				
			_setter_t::set ( var_ref, val );
			
		}
		
		inline static void get ( const var & var_ref, t & val ) {
			static_assert ( !std::is_array < t >::value, MSG_CANNOT_CONTAIN_ARRAYS );
			
			_getter_t::get ( var_ref, val );
		}
		
	};
	
public:
	
	// null setters
	inline var () : _type ( var_type_none ) {}

	inline var ( const std::nullptr_t & origin ) : _type ( var_type_none) {}
	
	virtual ~var() {
		if (_type == var_type_string ||
			_type == var_type_struct ||
			_type == var_type_pointer
		)
			delete _data._box_v;
	}

	// copy 
	inline var ( const var & origin ) :
		_data ( origin._data ),
		_type ( origin._type )
	{
		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer )
			_data._box_v = origin._data._box_v->copy ();
	}

	inline var operator = ( const var & origin ) {
		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer)
			delete _data._box_v;

		_data = origin._data;
		_type = origin._type;

		if (_type == var_type_string || _type == var_type_struct || _type == var_type_pointer )
			_data._box_v = origin._data._box_v->copy ();
		
		return origin;
	}

	// value setters
	template < class t >
	inline var ( const t & origin ) : _type (var_type_none) {
		_var_handler < t >::set ( *this, origin );
	}
	
	template < class t >
	inline t operator = ( const t & val ) {
		_var_handler < t >::set ( *this, val );
		return val;
	}
	
	// value getters
	template < class t >
	inline t as () const {
		t val;
		_var_handler < t >::get ( *this, val );
		return val;
	}

	template < class t >
	inline operator t () const {
		return as < t >();
	}

	// string specialization
	inline var ( const char * origin ) {
		_var_handler < std::string >::set ( *this, std::string ( origin ) );
	}

	inline const char * operator = ( const char * val ) {
		_var_handler < std::string >::set ( *this, std::string ( val ) );
		return val;
	}
	
};

#endif
