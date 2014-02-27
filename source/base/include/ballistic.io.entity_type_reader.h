
#ifndef _ballistic_io_entity_type_reader_h_
#define _ballistic_io_entity_type_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"
#include "ballistic.component_info.h"

namespace ballistic {
	namespace io {

		class entity_type_reader : public ipackage_element_reader {
		private:

			void load_component (
				tinyxml2::XMLElement * element,
				ballistic::resource_container & container,
				vector < component_info > & component_vector
				);

		public:

			virtual const char * name () const;

			virtual void load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container);

		};

	}
}

#endif
