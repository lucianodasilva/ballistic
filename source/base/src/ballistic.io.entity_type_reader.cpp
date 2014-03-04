#include "ballistic.io.entity_type_reader.h"
#include "ballistic.entity_type.h"
#include "ballistic.component_info.h"
#include "ballistic.component_constructor.h"
#include "ballistic.io.property_container_reader.h"

namespace ballistic {
	namespace io {

		const char * entity_type_reader::type () const {
			return "entity_type";
		}

		void entity_type_reader::load_component (
			const string & group_name,
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

		void entity_type_reader::load_group (
			const string & group_name,
			cpptoml::toml_group & group,
			ballistic::resource_container & container
		) {

			entity_type * new_type = new entity_type (text_to_id (group_name.c_str ()));

			// load components
			for (auto it : group) {
				if (!it.second->is_group ())
					continue;
				
				//load_component (
				//	it.first, 
				//	*group.get_group (it.first), 
				//	container
				//);
			}

			// load properties
			for (auto it : group) {
				if (!it.second->is_value ())
					continue;


			}



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