#include "ballistic.debug.h"
#include <iostream>

#ifdef BALLISTIC_DEBUG 

namespace ballistic {

	vector < debug_service::idebug_frontend * > debug_service::_frontends;

	debug_service::idebug_frontend::~idebug_frontend () {}

	void debug_service::console_frontend::print (const string & message) {
		cout << message;
	}

	void debug_service::initialize () {
		register_frontend (new console_frontend ());
	}

	void debug_service::register_frontend (debug_service::idebug_frontend * frontend) {
		_frontends.push_back (frontend);
	}

	void debug_service::print (const string & message) {
		for (debug_service::idebug_frontend * frontend : _frontends)
			frontend->print (message);
	}

}

#endif