
#ifndef _ballistic_package_reader_h_
#define _ballistic_package_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.package_loader.h"

namespace ballistic {

	class package_reader : public ipackage_element_reader {
	public:

		virtual const string & name ();

		virtual void load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container);

	};

}

#endif
