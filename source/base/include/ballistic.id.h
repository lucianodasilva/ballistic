#ifndef _ballistic_ballistic_id_h_
#define _ballistic_ballistic_id_h_

#include "ballistic.config.h"

#include <functional>
#include <string>

using namespace std;

namespace ballistic {
	
	typedef size_t id_t;
	
	inline id_t string_to_id ( const string & id_str ) {
		return hash < string > () ( id_str );
	}
	
}

#endif
