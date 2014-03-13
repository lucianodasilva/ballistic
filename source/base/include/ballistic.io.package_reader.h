
#ifndef _ballistic_io_package_reader_h_
#define _ballistic_io_package_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"

namespace ballistic {
	namespace io {

		class package_reader : public ipackage_group_reader {
		public:

			virtual const char * type () const;

			virtual void load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container);

		};
	}
}

#endif
