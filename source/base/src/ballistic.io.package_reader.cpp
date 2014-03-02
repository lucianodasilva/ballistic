#include "ballistic.io.package_reader.h"
#include "ballistic.io.package_loader.h"
#include "ballistic.io.istorage.h"

namespace ballistic {
	namespace io {

		const char * package_reader::type () const {
			return "include";
		}

		void package_reader::load_element (
			cpptoml::toml_group & group,
			ballistic::resource_container & container
			) {

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