//
//  ballistic.frontend.cpp
//  ballistic
//
//  Created by Luciano da Silva on 16/12/14.
//
//

#include "ballistic.frontend.h"
#include <ballistic.graphics.h>

namespace ballistic {
	
	ifrontend * create_frontend () {
		
		ifrontend * frontend = nullptr;
		
#ifdef BALLISTIC_OS_DARWIN
		frontend = new osx_desktop::frontend ();
#endif
		
		return frontend;
		
	}
	
}