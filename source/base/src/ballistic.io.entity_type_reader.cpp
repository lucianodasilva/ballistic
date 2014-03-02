#include "ballistic.io.entity_type_reader.h"
#include "ballistic.entity_type.h"
#include "ballistic.component_info.h"
#include "ballistic.component_constructor.h"
#include "ballistic.io.property_container_reader.h"

namespace ballistic {
	namespace io {

		const char * entity_type_reader::type () const {
			return "entity";
		}

		void entity_type_reader::load_component (
			cpptoml::toml_group & group,
			ballistic::resource_container & container,
			vector < component_info > & component_vector
		) {

			//auto cursor = element->FirstChildElement ();
			//
			//while (cursor) {
			//	component_vector.push_back (component_info ());
			//	component_info & info = component_vector.back ();
			//
			//	auto ctor = dynamic_cast <icomponent_constructor *> (container [text_to_id (cursor->Name ())]);
			//
			//	if (ctor) {
			//		info.ctor (ctor);
			//		property_container_reader::read (cursor, container, info.properties);
			//	}
			//	debug_run (
			//	else
			//	debug_error ("component constructor " << cursor->Name () << "not defined");
			//	);
			//
			//	cursor = cursor->NextSiblingElement ();
			//}
		}

		void entity_type_reader::load_element (
			cpptoml::toml_group & group,
			ballistic::resource_container & container
			) {

			//const char * type_name = element->Attribute ("name");
			//
			//entity_type * type = new entity_type (text_to_id (type_name));
			//
			//property_container_reader::read (
			//	element,
			//	container,
			//	type->properties
			//	);
			//
			//load_component (element, container, type->components);
			//container.add_to_level (type);
		}

	}
}