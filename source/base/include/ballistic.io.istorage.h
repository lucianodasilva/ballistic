//
//  ballistic.resources.istorage.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_io_istorage_h_
#define _ballistic_io_istorage_h_

#include <iostream>
#include <string>

#include "ballistic.resource_container.h"

using namespace std;

namespace ballistic {

	class iresource;

	namespace io {

		class iloader;

		class istorage {
		public:

			virtual ~istorage () {};

			virtual bool contains (const string & path) = 0;
			virtual bool load (iloader * loader, const string & path, ballistic::resource_container & stack) = 0;

		};
	}

}

#endif
