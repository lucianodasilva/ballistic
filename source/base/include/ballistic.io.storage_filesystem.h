//
//  ballistic.resources.storage_filesystem.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_io_storage_filesystem_h_
#define _ballistic_io_storage_filesystem_h_

#include <iostream>
#include <string>

#include "ballistic.io.istorage.h"

using namespace std;

namespace ballistic {
	namespace io {

		class storage_filesystem : public istorage {
		public:

			virtual ~storage_filesystem ();

			virtual bool contains (const string & path);

			virtual bool load (iloader * loader, const string & path, ballistic::resource_container & container, const id_t & id);

		};
	}
}

#endif
