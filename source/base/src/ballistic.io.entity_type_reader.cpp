#include "ballistic.io.entity_type_reader.h"
#include "ballistic.entity_type.h"
#include "ballistic.component_info.h"
#include "ballistic.component_constructor.h"

namespace ballistic {
	namespace io {

		const char * entity_type_reader::type () const {
			return "entity_type";
		}

		void entity_type_reader::load_component (
			const tinyxml2::XMLElement * element,
			ballistic::resource_container & container,
			entity_type * new_type
		) {

			// load respective component constructor
			icomponent_constructor * ctor = container [text_to_id (element->Name ())];

			if (!ctor) {
				debug_error ("component constructor " << element->Name () << "not defined");
				return;
			}

			new_type->components.push_back (component_info ());
			component_info & new_info = new_type->components.back ();

			// load component expected parameters
			ctor->require_properties (new_type, new_info);
			new_info.ctor (ctor);

			auto prop_cursor = element->FirstAttribute ();

			while (prop_cursor) {
				if (strcmp (prop_cursor->Name (), "name") != 0) {
					id_t property_id = text_to_id (prop_cursor->Name ());

					if (new_info.properties.contains (property_id)) {
						new_info.properties [property_id].property->parse (prop_cursor);
					} else {
						debug_print ("unrequested entity property \"" << prop_cursor->Name () << "\". value not set");
					}
				}

				prop_cursor = prop_cursor->Next ();
			}

		}

		void entity_type_reader::load_element (
			const tinyxml2::XMLElement * element,
			ballistic::resource_container & container
		) {

			const char * type_name = element->Attribute ("name");
			entity_type * new_type = new entity_type (text_to_id (type_name));

			// load components
			auto comp_cursor = element->FirstChildElement ();

			while (comp_cursor) {
				load_component (comp_cursor, container, new_type);
				comp_cursor = comp_cursor->NextSiblingElement ();
			}

			// load properties
			auto prop_cursor = element->FirstAttribute ();

			while (prop_cursor) {
				if (strcmp (prop_cursor->Name (), "name") != 0) {
					id_t property_id = text_to_id (prop_cursor->Name ());

					if (new_type->properties.contains (property_id)) {
						new_type->properties [property_id].property->parse (prop_cursor);
					} else {
						debug_print ("unrequested entity property \"" << prop_cursor->Name () << "\". value not set");
					}
				}

				prop_cursor = prop_cursor->Next ();
			}

			container.add_to_level (new_type);

		}

	}
}