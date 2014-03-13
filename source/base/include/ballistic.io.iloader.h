//
//  ballistic.iloader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_io_iloader_h_
#define _ballistic_io_iloader_h_

#include <string>
#include <iostream>

#include "ballistic.resource_container.h"

using namespace std;

namespace ballistic {
	namespace io {

		class iloader {
		public:

			virtual bool handles (const string & name) = 0;

			virtual bool load (istream & source, uint32_t length, ballistic::resource_container & container) = 0;

			virtual ~iloader () {};

		};
	}
}

#endif
