#ifndef _ballistic_resource_entity_loader_h_
#define _ballistic_resource_entity_loader_h_

#include "ballistic.resources.iloader.h"

namespace ballistic {
	namespace resources {
		
		class entity_loader : public iloader {
		public:
			
			virtual bool handles ( const string & name );
			
			virtual bool load ( istream & source, ballistic::resources::stack & stack );
			
		};
		
	}
}

#endif
