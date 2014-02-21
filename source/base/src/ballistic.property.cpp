#include "ballistic.property.h"
#include "ballistic.entity.h"

namespace ballistic {

	iproperty::~iproperty () {}

	namespace details {

		null_property_container null_property_container::static_instance;

		void null_property_container::property_changed_event (iproperty * changed_property) {}

	}

}