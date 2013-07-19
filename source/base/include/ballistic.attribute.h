#ifndef _ballistic_attribute_h
#define _ballistic_attribute_h

#include "ballistic.id.h"
#include "ballistic.var.h"

#include <map>
#include <vector>

using namespace std;

namespace ballistic {
		
	class entity;
		
	class attribute {
	private:
			
		var			_value;
		id_t		_id;
		entity *	_parent;

		void raise_changed_event ();
			
	public:
			
		attribute ();
		attribute ( id_t id );
		attribute ( entity * parent, id_t id );
		attribute ( const attribute & orig );
		
		inline operator var ();

		template < class t >
		inline operator t ();
		
		template < class t >
		inline t as ();

		template < class t >
		inline var & operator = ( const t & value );
		
		inline var & operator = ( const var & value );
			
		id_t get_id ();

	};
	
	attribute::operator var () {
		return _value;
	}
		
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
	
	var & attribute::operator = ( const var & value ) {
		_value = value;
		raise_changed_event ();
		return _value;
	}
	
	typedef map < id_t, attribute > attribute_map_t;
}

#endif
