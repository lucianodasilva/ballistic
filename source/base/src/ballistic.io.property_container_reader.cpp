#include "ballistic.io.property_container_reader.h"

#include "ballistic.convert.h"
#include "ballistic.math.h"

#include "ballistic.math.h"

namespace ballistic {
	namespace io {

		void property_container_reader::read (
			tinyxml2::XMLElement * element,
			ballistic::resource_container & resources,
			property_container & container
		){

			tinyxml2::XMLElement * cursor = element->FirstChildElement ();

			while (cursor) {
			
				const char * value_ptr = cursor->Attribute ("value");
				if (!value_ptr) {
					debug_error ("package property " << cursor->Name () << " has no value. property not added!");
				} else {

					string value = value_ptr;

					iproperty * p_val = nullptr;

					const char * prop_type_ptr = cursor->Attribute ("type");

					if (prop_type_ptr) {

						string prop_type = prop_type_ptr;

						if (!prop_type.empty ()) {
							if (prop_type == "int")
								container.require < int32_t > (
								text_to_id (cursor->Name ()),
								convert_to < int32_t > (value)
								);
							else if (prop_type == "uint")
								container.require < uint32_t > (
								text_to_id (cursor->Name ()),
								convert_to < uint32_t > (value)
								);
							else if (prop_type == "real")
								container.require < real > (
								text_to_id (cursor->Name ()),
								convert_to < real > (value)
								);
							else if (prop_type == "bool")
								container.require < bool > (
								text_to_id (cursor->Name ()),
								convert_to < bool > (value)
								);
							else if (prop_type == "vec2") {
								vec2 tmp;
								convert_vectors (value, tmp);
								container.require < vec2 > (
									text_to_id (cursor->Name ()),
									tmp
								);
							} else if (prop_type == "vec3") {
								vec3 tmp;
								convert_vectors (value, tmp);
								container.require < vec3 > (
									text_to_id (cursor->Name ()),
									tmp
								);
							} else if (prop_type == "vec4") {
								vec4 tmp;
								convert_vectors (value, tmp);
								container.require < vec4 > (
									text_to_id (cursor->Name ()),
									tmp
								);
							} else if (prop_type == "color") {
								color tmp;
								convert_vectors (value, tmp);
								container.require < color > (
									text_to_id (cursor->Name ()),
									tmp
								);
							} else if (prop_type == "res")
								container.require < id_t > (
									text_to_id (cursor->Name ()),
									text_to_id (value.c_str ())
								);
							else {
								debug_print ("[ballistic::resources::property_container_reader::read] Unknown property type \"" << prop_type << "\". No conversion.");
							}

						} // if (!prop_type.empty ())
					} else {
						container.require < string > (
							text_to_id (cursor->Name ()),
							value
							);
					} // if (prop_type_ptr)

				} // if (!value_ptr)
				
				cursor = cursor->NextSiblingElement ();
			} // while (cursor)
		}
	}
}