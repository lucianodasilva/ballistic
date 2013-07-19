//
//  ballistic.resources.iloader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_iloader_h_
#define _ballistic_resources_iloader_h_

#include <string>
#include <iostream>

#include "ballistic.resources.stack.h"

using namespace std;

namespace ballistic {
	namespace resources {
		
		class iloader {
		public:
			
			virtual bool handles ( const string & name ) = 0;
			
			virtual bool load ( istream & source, ballistic::resources::stack & stack ) = 0;
			
			virtual ~iloader () {};
		};
		
	}
}

#endif
