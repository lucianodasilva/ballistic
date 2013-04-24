#ifndef _ballistic_engine_message_h_
#define _ballistic_engine_message_h_

#include "ballistic.var.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

namespace ballistic {
	namespace engine {

		class message {
		public:

			typedef size_t message_id_t;

		private:
			
			map < size_t, var >		_attributes;
			message_id_t			_message_id;

		public:

			inline message ( message_id_t message_id );
			inline message ( const message & orig );

			inline message_id_t get_id () const;

			inline bool has_attribute ( size_t attribute_key ) const;
			inline bool has_attribute ( const string & key ) const;

			inline var & operator [] ( size_t attribute_key );
			inline var & operator [] ( const string & key );

		};

		message::message ( message_id_t message_id ) : _message_id (message_id) {}

		message::message ( const message & orig ) : _message_id ( orig._message_id ), _attributes (orig._attributes) {}

		inline message::message_id_t message::get_id () const { return _message_id; }

		bool message::has_attribute ( size_t attribute_key ) const {
			return _attributes.find (attribute_key) != _attributes.end ();
		}

		bool message::has_attribute ( const string & key ) const {
			return has_attribute ( hash < string >() (key) ) ;
		}

		var & message::operator [] ( size_t attribute_key ) {
			return _attributes [attribute_key];
		}

		var & message::operator [] ( const string & key ) {
			return operator [] ( hash < string > ()(key) );
		}
		
	}
}

#endif
