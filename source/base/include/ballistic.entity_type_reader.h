
#ifndef _ballistic_entity_type_reader_h_
#define _ballistic_entity_type_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.package_loader.h"
#include "ballistic.component_info.h"

namespace ballistic {

	class entity_type_reader : public ipackage_element_reader {
	private:

		void load_component (
			tinyxml2::XMLElement * element,
			ballistic::resource_container & stack,
			vector < component_info > & component_vector
		);
	
	public:

		virtual const string & name ();

		virtual void load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container);

	};

}

#endif
