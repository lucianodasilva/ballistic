#ifndef _ballistic_debug_h_
#define _ballistic_debug_h_

#include "ballistic.config.h"
#include "ballistic.common_id.h"

#ifdef BALLISTIC_DEBUG

#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace ballistic {
	
	class debug_service {
	public:
		
		class idebug_frontend {
		public:

			virtual void print (const string & message) = 0;

			virtual ~idebug_frontend ();

		};

		class console_frontend : public idebug_frontend {
		public:
			virtual void print (const string & message);
		};

		struct message {
			stringstream message_stream;

			inline virtual ~message ();

			template < class T >
			inline message & operator << (const T & v);

			inline message & operator << (const id_t & id);
		};

	private:

		static vector < idebug_frontend * > _frontends;

	public:

		static void initialize ();

		static void register_frontend (idebug_frontend * frontend);

		static void print (const string & message);

	};

	debug_service::message::~message () {
		message_stream << std::endl;
		debug_service::print (message_stream.str ());
	}

	template < class T >
	debug_service::message & debug_service::message::operator << (const T & v) {
		message_stream << v;
		return *this;
	}

	debug_service::message & debug_service::message::operator << (const id_t & v) {
		message_stream << "[" << v.text << "|" << v.key << "]";
		return *this;
	}
	
}

#	define debug_run(x) \
	x

#	define debug_init() ballistic::debug_service::initialize ()
#	define debug_print(x) {ballistic::debug_service::message () << x;}
#	define debug_error(x) {ballistic::debug_service::message () << x << " | " << __FILE__ << " @ " << __LINE__;}

#	define debug_assert(condition, x) if (condition) { debug_error (x) }

#	define debug_add_frontend(x) ballistic::debug_service::register_frontend (x)

#else
#	define debug_run(x) {}
#	define debug_init() {}
#	define debug_print(x) {}
#	define debug_error(x) {}
#	define debug_assert(condition, x) {}
#	define debug_add_frontend(x) {}
#endif

#endif