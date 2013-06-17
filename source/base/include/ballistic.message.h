#ifndef _ballistic_message_h_
#define _ballistic_message_h_

#include "ballistic.var.h"
#include "ballistic.id.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

namespace ballistic {

	class entity;

	class message {
	private:
			
		map < id_t, var >	_attributes;
		id_t				_id;
		entity *			_sender;

	public:

		inline message ( entity * sender, id_t message_id );
		inline message ( const message & orig );

		inline id_t get_id () const;
		inline entity &		get_sender () const;

		inline bool has_attribute ( id_t attribute_key ) const;
		inline bool has_attribute ( const string & key ) const;

		inline var & operator [] ( id_t attribute_key );
		inline var & operator [] ( const string & key );

	};

	message::message ( entity * sender, id_t message_id ) : _id (message_id), _sender (sender) {}

	message::message ( const message & orig ) : _attributes (orig._attributes), _id ( orig._id ), _sender (orig._sender) {}

	inline id_t message::get_id () const { return _id; }

	inline entity & message::get_sender () const { return *_sender; }

	bool message::has_attribute ( id_t attribute_key ) const {
		return _attributes.find (attribute_key) != _attributes.end ();
	}

	bool message::has_attribute ( const string & key ) const {
		return has_attribute ( string_to_id (key) ) ;
	}

	var & message::operator [] ( id_t attribute_key ) {
		return _attributes [attribute_key];
	}

	var & message::operator [] ( const string & key ) {
		return operator [] ( string_to_id(key) );
	}
}

#endif
