#include "ballistic.io.package_reader.h"
#include "ballistic.io.package_loader.h"
#include "ballistic.io.istorage.h"

namespace ballistic {
	namespace io {

		const char * package_reader::type () const {
			return "package";
		}

		void package_reader::load_group (
			const string & group_name,
			cpptoml::toml_group & group,
			ballistic::resource_container & container
			) {

				debug_error ("NOT IMPLEMENTED");


			//string source = element->Attribute ("source");
			//istorage * storage = container.find_storage (source);
			//
			//if (storage) {
			//	package_loader loader;
			//	storage->load (&loader, source, container);
			//}

		}
	}
}