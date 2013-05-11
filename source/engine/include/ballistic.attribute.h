#ifndef _ballistic_attribute_h
#define _ballistic_attribute_h

#include "ballistic.var.h"

namespace ballistic {
		
	class entity;
		
	class attribute {
	public:
		typedef size_t id_t;
	private:
			
		var			_value;
		id_t		_id;
		entity *	_parent;

		void raise_changed_event ();
			
	public:
			
		attribute ();
		attribute ( entity * parent, id_t id );
		attribute ( const attribute & orig );

		template < class t >
		inline operator t ();
		
		template < class t >
		inline t as ();

		template < class t >
		var & operator = ( const t & value );
			
		id_t get_id ();

	};
		
	template < class t >
	attribute::operator t () {
		return _value.operator t ();
	}

	template < class t >
	t attribute::as () {
		return _value.as < t > ();
	}

	template < class t >
	var & attribute::operator = (const t & value) {
		_value.operator = < t > (value);
		raise_changed_event ();

		return _value;
	}
}

#endif
