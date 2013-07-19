//
//  ballistic.resource.package_loader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#ifndef _ballistic_resource_package_loader_h_
#define _ballistic_resource_package_loader_h_

#include "ballistic.resources.iloader.h"
#include "ballistic.resources.stack.h"

namespace ballistic {
	namespace resources {
		
		class package_loader : public iloader {
		private:

		public:
			
			virtual bool handles ( const string & name );
			
			virtual bool load ( istream & source, ballistic::resources::stack & stack );
			
		};
		
	}
}

#endif
