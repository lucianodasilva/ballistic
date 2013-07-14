//
//  ballistic.resources.storage_filesystem.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_storage_filesystem_h_
#define _ballistic_resources_storage_filesystem_h_

#include <iostream>
#include <string>

#include "ballistic.resources.istorage.h"

using namespace std;

namespace ballistic {
	namespace resources {
		
		class storage_filesystem : public istorage {
		public:
			
			virtual ~storage_filesystem ();
			
			virtual bool contains ( const string & path );
			
			virtual iresource * load ( iloader * loader, const string & path );
			
		};
		
	}
}

#endif
