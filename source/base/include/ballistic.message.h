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
			
		map < id_t, var >	_properties;
		id_t				_id;
		entity *			_sender;

	public:

		inline message (id_t message_id);
		inline message ( entity * sender, id_t message_id );
		inline message ( const message & orig );

		inline id_t get_id () const;

		inline entity * get_sender () const;
		inline void set_sender (entity * s);

		inline bool has_property ( id_t property_key ) const;

		inline var & operator [] ( id_t property_key );

#ifdef BALLISTIC_DEBUG
		inline bool has_property (const string & key) const;
		inline var & operator [] (const string & key);
#endif // BALLISTIC_DEBUG


	};

	message::message (id_t message_id) : _id (message_id), _sender (nullptr) {}

	message::message ( entity * sender, id_t message_id ) : _id (message_id), _sender (sender) {}

	message::message ( const message & orig ) : _properties (orig._properties), _id ( orig._id ), _sender (orig._sender) {}

	inline id_t message::get_id () const { return _id; }

	inline entity * message::get_sender () const { return _sender; }

	inline void message::set_sender (entity * s) { _sender = s; }

	bool message::has_property ( id_t property_key ) const {
		return _properties.find (property_key) != _properties.end ();
	}

	var & message::operator [] ( id_t property_key ) {
		return _properties [property_key];
	}

#ifdef BALLISTIC_DEBUG

	bool message::has_property (const string & key) const {
		return has_property (string_to_id (key));
	}

	var & message::operator [] (const string & key) {
		return operator [] ( string_to_id(key) );
	}

#endif // !BALLISTIC_DEBUG

	 
}

#endif
