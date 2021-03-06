#include "ballistic.io.package_reader.h"
#include "ballistic.io.package_loader.h"
#include "ballistic.io.istorage.h"

namespace ballistic {
	namespace io {

		const char * package_reader::type () const {
			return "package";
		}

		void package_reader::load_element (
			const tinyxml2::XMLElement * element,
			ballistic::resource_container & container
		) {
			string source = element->Attribute ("source");
			istorage * storage = container.find_storage (source);
			
			if (storage) {
				storage->load (container.package_loader (), source, container, id::null);
			}

		}
	}
}