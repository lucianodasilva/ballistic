#include "ballistic.io.property_container_reader.h"

#include "ballistic.convert.h"
#include "ballistic.math.h"

#include "ballistic.math.h"

namespace ballistic {
	namespace io {

		void property_container_reader::read (
			cpptoml::toml_group & group,
			ballistic::resource_container & resources,
			property_container & container
		){
			//auto cursor = element->FirstAttribute ();
			//
			//while (cursor) {
			//
			//	if (strcmp (cursor->Name (), "name") != 0)
			//		container.require < string > (text_to_id (cursor->Name ()), cursor->Value ());
			//
			//	cursor = cursor->Next ();
			//} 
		}
	}
}