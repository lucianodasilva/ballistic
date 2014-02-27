
#ifndef _ballistic_io_package_reader_h_
#define _ballistic_io_package_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"

namespace ballistic {
	namespace io {

		class package_reader : public ipackage_element_reader {
		public:

			virtual const char * name () const;

			virtual void load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container);

		};
	}
}

#endif
