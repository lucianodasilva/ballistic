
#ifndef _ballistic_io_animation_sequence_reader_h_
#define _ballistic_io_animation_sequence_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"
#include "ballistic.component_info.h"

namespace ballistic {

	class entity_type;

	namespace io {

		class animation_sequence_reader : public ipackage_group_reader {
		private:

			void load_component (
				const tinyxml2::XMLElement * element,
				ballistic::resource_container & container,
				entity_type * new_type
				);

		public:

			virtual const char * type () const;

			virtual void load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container);

		};

	}
}

#endif
