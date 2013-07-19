//
//  ballistic.resource.entity_loader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#ifndef _ballistic_resource_entity_loader_h_
#define _ballistic_resource_entity_loader_h_

#include "ballistic.resources.iloader.h"

namespace ballistic {
	namespace resources {
		
		class entity_loader : public iloader {
		public:
			
			virtual bool handles ( const string & name );
			
			virtual iresource * load ( istream & source, ballistic::resources::stack & stack );
			
		};
		
	}
}

#endif
