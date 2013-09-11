//
//  ballistic.resources.istorage.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_istorage_h_
#define _ballistic_resources_istorage_h_

#include <iostream>
#include <string>

#include "ballistic.resources.stack.h"

using namespace std;

namespace ballistic {
	namespace resources {
		
		class iloader;
		class iresource;
		
		class istorage {
		public:
	
			virtual ~istorage (){};
	
			virtual bool contains ( const string & path ) = 0;
			virtual bool load ( iloader * loader, const string & path, ballistic::resources::stack & stack ) = 0;
	
		};

	}
}

#endif
