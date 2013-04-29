#ifndef _ballistic_engine_message_h_
#define _ballistic_engine_message_h_

#include "ballistic.var.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

namespace ballistic {
	namespace engine {

		class entity;

		typedef size_t message_id_t;
		typedef size_t message_attribute_id_t;

		class message {
		private:
			
			map < message_attribute_id_t, var >		_attributes;
			message_id_t			_message_id;
			entity *				_sender;

		public:

			inline message ( entity * sender, message_id_t message_id );
			inline message ( const message & orig );

			inline message_id_t get_id () const;
			inline entity *		get_sender () const;

			inline bool has_attribute ( message_attribute_id_t attribute_key ) const;
			inline bool has_attribute ( const string & key ) const;

			inline var & operator [] ( message_attribute_id_t attribute_key );
			inline var & operator [] ( const string & key );

		};

		message::message ( entity * sender, message_id_t message_id ) : _message_id (message_id), _sender (sender) {}

		message::message ( const message & orig ) : _attributes (orig._attributes), _message_id ( orig._message_id ), _sender (orig._sender) {}

		inline message_id_t message::get_id () const { return _message_id; }

		inline entity * message::get_sender () const { return _sender; }

		bool message::has_attribute ( message_attribute_id_t attribute_key ) const {
			return _attributes.find (attribute_key) != _attributes.end ();
		}

		bool message::has_attribute ( const string & key ) const {
			return has_attribute ( hash < string >() (key) ) ;
		}

		var & message::operator [] ( message_attribute_id_t attribute_key ) {
			return _attributes [attribute_key];
		}

		var & message::operator [] ( const string & key ) {
			return operator [] ( hash < string > ()(key) );
		}
		
	}
}

#endif
