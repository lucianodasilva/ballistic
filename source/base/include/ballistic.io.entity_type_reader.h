
#ifndef _ballistic_io_entity_type_reader_h_
#define _ballistic_io_entity_type_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"
#include "ballistic.component_info.h"

namespace ballistic {

	class entity_type;

	namespace io {

		class entity_type_reader : public ipackage_group_reader {
		private:

			void load_component (
				const string & group_name,
				cpptoml::toml_group & group,
				ballistic::resource_container & container,
				entity_type * new_type
				);

		public:

			virtual const char * type () const;

			virtual void load_group (const string & group_name, cpptoml::toml_group & group, ballistic::resource_container & container);

		};

	}
}

#endif
