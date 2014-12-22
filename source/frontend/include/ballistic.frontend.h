#ifndef _ballistic_frontend_h_
#define _ballistic_frontend_h_

#define BALLISTIC_FRONTEND_EXPORT

#include "ballistic.frontend.defines.h"
#include "ballistic.ifrontend.h"
#include "ballistic.win_frontend.h"
#include "ballistic.osx_frontend.h"


namespace ballistic {
	
	ifrontend * create_frontend ();
	
}

#endif