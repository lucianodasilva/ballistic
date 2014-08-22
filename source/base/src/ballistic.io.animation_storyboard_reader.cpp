#include "ballistic.io.animation_storyboard_reader.h"

#include "ballistic.animation.function.h"
#include "ballistic.animation.storyboard.h"
#include "ballistic.animation.function_type.h"

namespace ballistic {
	namespace io {

		const char * animation_storyboard_reader::type () const {
			return "storyboard";
		}

		void animation_storyboard_reader::load_action (
			const tinyxml2::XMLElement * element,
			ballistic::resource_container & container,
			animation::storyboard * new_story
		){

			animation::ifunction_type * func_type = container [text_to_id (element->Name ())];

			if (!func_type) {
				debug_error ("function \"" << element->Name () << "\" not defined");
				return;
			}

			containers::property_container parameters;


			func_type->require_parameters (parameters);
			animation::storyboard::action::require_parameters (parameters);

			auto prop_cursor = element->FirstAttribute ();

			while (prop_cursor) {

				id_t property_id = text_to_id (prop_cursor->Name ());
				
				if (parameters.contains (property_id)) {
					parameters [property_id].property->parse (prop_cursor);
				} else {
					debug_print ("unrequested entity property \"" << prop_cursor->Name () << "\". value not set");
				}
				
				prop_cursor = prop_cursor->Next ();
			}

			new_story->add_action (parameters, func_type->create (parameters));

		}

		void animation_storyboard_reader::load_element (
			const tinyxml2::XMLElement * element,
			ballistic::resource_container & container
			) {

			const char * name = element->Attribute ("name");

			// create new story instance
			auto new_story = new animation::storyboard (text_to_id (name));

			container.add_to_level (new_story);

			auto cursor = element->FirstChildElement ();

			while (cursor) {
				load_action (cursor, container, new_story);
				cursor = cursor->NextSiblingElement ();
			}

		}

	}
}