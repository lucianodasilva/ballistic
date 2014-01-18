#include "ballistic.graphics.resources.mesh_package_type.h"

#include "ballistic.graphics.imesh.h"

#include <vector>

using namespace std;

namespace ballistic {
	namespace graphics {
		namespace resources {

			mesh_package_type::mesh_package_type (idevice * device) : _device (device) {}

			string mesh_package_type::get_name () {
				return "mesh";
			}

			istream & mesh_package_type::get_line (istream & stream, string & trim, char delimiter) {
				char c;

				trim.clear ();

				while (stream.get (c).good ()) {
					if (c == '\n' || c == '\r')
						continue;

					if (c == delimiter || stream.peek () == std::char_traits<char>::eof ())
						return stream;

					trim.append (1, c);
				}

				return stream;
			}

			void mesh_package_type::load_element (tinyxml2::XMLElement * element, ballistic::resources::stack & stack) {

				string name = element->Attribute ("name");

				imesh * mesh = _device->create_mesh ();

				mesh_attribute m_attribute = mesh_attribute ();

				vector < real >		position;
				vector < real >		uv;
				vector < uint16_t >	index;

				tinyxml2::XMLElement * cursor = element->FirstChildElement ();
				while (cursor) {

					if (strcmp (cursor->Name (), "position") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_position);

						stringstream ss (cursor->GetText ());
						string value;

						while (get_line (ss, value, ',')) {
							position.push_back (convert_to < real > (value));
						}


						if (position.size () % 3 != 0) {
							debug_error ("[ballistic::graphics::resources::mesh_package_type::load_element] mesh position vector not multiple of 3!");
							delete mesh;
							return;
						}
					} else if (strcmp (cursor->Name (), "uv") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_uv);

						stringstream ss (cursor->GetText ());
						string value;

						while (get_line (ss, value, ',')) {
							uv.push_back (convert_to < real > (value));
						}

						if (uv.size () % 2 != 0) {
							debug_error ("[ballistic::graphics::resources::mesh_package_type::load_element] mesh uv vector not multiple of 2!");
							delete mesh;
							return;
						}

						if (uv.size () / 2 != position.size () / 3) {
							debug_error ("[ballistic::graphics::resources::mesh_package_type::load_element] mesh uv vector size does not match the size of the position vector!");
							delete mesh;
							return;
						}
					} else if (strcmp (cursor->Name (), "index") == 0) {
						stringstream ss (cursor->GetText ());
						string value;

						while (get_line (ss, value, ',')) {
							index.push_back (convert_to < uint16_t > (value));
						}

					}

					cursor = cursor->NextSiblingElement ();
				}

				// merge data
				uint32_t buffer_size =
					(m_attribute & mesh_attribute_position ? position.size () * sizeof (real) : 0) +
					(m_attribute & mesh_attribute_uv ? uv.size () * sizeof (real) : 0)
				;


				uint8_t * data_buffer = new uint8_t [buffer_size];
				real * data_cursor = (real *)data_buffer;
				for (uint32_t i = 0; i < position.size () / 3; ++i) {

					if (m_attribute & mesh_attribute_position) {
						uint32_t offset = i * 3;

						for (uint32_t j = 0; j < 3; ++j)
							*data_cursor++ = position [offset++];
					}
					
					if (m_attribute & mesh_attribute_uv) {
						uint32_t offset = i * 2;

						for (uint32_t j = 0; j < 2; ++j)
							*data_cursor++ = uv [offset++];
					}

				}

				mesh->set_data (data_buffer, buffer_size, index.data (), index.size () * sizeof (uint16_t), m_attribute, false);

				delete [] data_buffer;

				stack.add_to_level (string_to_id (name), mesh);

			}

		}
	}
}