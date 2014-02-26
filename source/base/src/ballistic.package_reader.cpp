#include "ballistic.package_reader.h"
#include "ballistic.package_loader.h"

namespace ballistic {

	const string & package_reader::name () {
		return "include";
	}

	void package_reader::load_element (
		tinyxml2::XMLElement * element, 
		ballistic::resource_container & container
	) {
		
		string source = element->Attribute ("source");
		istorage * storage = container.find_storage (source);

		if (storage) {
			package_loader loader;
			storage->load (&loader, source, container);
		}

	}
		
}