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
			entity_type * new_type
		) {

			// load respective component constructor
			auto ctor = dynamic_cast <icomponent_constructor *> (container [text_to_id (group_name.c_str ())]);

			if (!ctor) {
				debug_error ("component constructor " << group_name << "not defined");
				return;
			}

			new_type->components.push_back (component_info ());
			component_info & new_info = new_type->components.back ();

			// load component expected parameters
			ctor->require_properties (new_type, new_info);

			for (auto it : group) {

				if (!it.second->is_value ()) {
					debug_print ("element \"" << it.first << "\" has unexpected type");
					continue;
				}

				// try to load arguments
				id_t property_id = text_to_id (it.first.c_str ());

				if (!new_info.properties.contains (property_id)) {
					debug_print ("unexpected argument property \"" << it.first << "\" for component \"" << group_name << "\"");
					continue;
				}

				new_info.properties [property_id].prop->parse (it.second);
			}

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

				load_component (it.first, *group.get_group (it.first), container, new_type);
			}

			// load properties
			for (auto it : group) {
				if (!it.second->is_value ())
					continue;

				id_t property_id = text_to_id (it.first.c_str ());

				if (!new_type->properties.contains (property_id)) {
					debug_print ("unrequested entity property \"" << it.first << "\". value not set");
					continue;
				}

				new_type->properties [property_id].prop->parse (it.second);
			}

		}

	}
}