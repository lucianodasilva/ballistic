//
//  ballistic.iresource.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_iresource_h
#define _ballistic_resources_iresource_h

namespace ballistic {
	namespace resources {
		class iresource {
		public:
			virtual void dispose () = 0;
		
			virtual ~iresource ();
		};
	}
}

#endif
