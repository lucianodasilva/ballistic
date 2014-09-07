#include "ballistic.graphics.io.mesh_package_reader.h"

#include "ballistic.graphics.imesh.h"

#include <vector>

using namespace std;

namespace ballistic {
	namespace graphics {
		namespace io {

			mesh_package_reader::mesh_package_reader (idevice * device) : _device (device) {}

			const char * mesh_package_reader::type () const {
				return "mesh";
			}

			istream & mesh_package_reader::get_line (istream & stream, string & trim, char delimiter) {
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

			void mesh_package_reader::load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container) {

				const char * name = element->Attribute ("name");
				
				imesh * mesh = _device->create_mesh (text_to_id (name));
				
				mesh_attribute m_attribute = mesh_attribute ();
				
				vector < real >		position;
				vector < real >		uv;
				//vector < real >		normal;
				vector < uint32_t >		bone_index;
				vector < real >		bone_weight;
				vector < uint16_t >	index;
				
				auto * cursor = element->FirstChildElement ();
				while (cursor) {
				
					if (strcmp (cursor->Name (), "position") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_position);
				
						stringstream ss (cursor->GetText ());
						string value;
				
						while (get_line (ss, value, ',')) {
							position.push_back (convert_to < real > (value));
						}
				
				
						if (position.size () % 3 != 0) {
							debug_error ("mesh position vector not multiple of 3!");
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
							debug_error ("mesh uv vector not multiple of 2!");
							delete mesh;
							return;
						}
				
						if (uv.size () / 2 != position.size () / 3) {
							debug_error ("mesh uv vector size does not match the size of the position vector!");
							delete mesh;
							return;
						}
					/*} else if (strcmp (cursor->Name (), "normal") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_normal);
				
						stringstream ss (cursor->GetText ());
						string value;
				
						while (get_line (ss, value, ',')) {
							normal.push_back (convert_to < real > (value));
						}
				
						if (normal.size () % 3 != 0) {
							debug_error ("mesh normal vector not multiple of 3!");
							delete mesh;
							return;
						}
				
						if (normal.size () / 3 != position.size () / 3) {
							debug_error ("mesh normal vector size does not match the size of the position vector!");
							delete mesh;
							return;
						}*/
					} else if (strcmp (cursor->Name (), "bone_index") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_bone_index);

						stringstream ss (cursor->GetText ());
						string value;

						while (get_line (ss, value, ',')) {
							bone_index.push_back (convert_to < uint32_t > (value));
						}

						if (bone_index.size () % 2 != 0) {
							debug_error ("mesh bone index vector not multiple of 2!");
							delete mesh;
							return;
						}

						if (bone_index.size () / 2 != position.size () / 3) {
							debug_error ("mesh bone index vector size does not match the size of the position vector!");
							delete mesh;
							return;
						}

					} else if (strcmp (cursor->Name (), "bone_weight") == 0) {
						m_attribute = (mesh_attribute)(m_attribute | mesh_attribute_bone_weight);

						stringstream ss (cursor->GetText ());
						string value;

						while (get_line (ss, value, ',')) {
							bone_weight.push_back (convert_to < real > (value));
						}

						if (bone_weight.size () != position.size () / 3) {
							debug_error ("mesh bone_weight size does not match the size of the position vector!");
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
					(m_attribute & mesh_attribute_uv ? uv.size () * sizeof (real) : 0) +
					(m_attribute & mesh_attribute_bone_index ? bone_index.size () * sizeof (uint32_t) : 0 ) +
					(m_attribute & mesh_attribute_bone_weight ? bone_weight.size () * sizeof (real) : 0)
				;
				
				
				uint8_t * data_buffer = new uint8_t [buffer_size];
				//real * data_cursor = (real *)data_buffer;
				uint8_t * data_cursor = data_buffer;
				for (uint32_t i = 0; i < position.size () / 3; ++i) {
				
					if (m_attribute & mesh_attribute_position) {
						uint32_t offset = i * 3;
				
						for (uint32_t j = 0; j < 3; ++j) {
							*((real *)data_cursor) = position [offset++];
							data_cursor += sizeof (real);
						}
					}
					
					if (m_attribute & mesh_attribute_uv) {
						uint32_t offset = i * 2;
				
						for (uint32_t j = 0; j < 2; ++j) {
							*((real *)data_cursor) = uv [offset++];
							data_cursor += sizeof (real);
						}
					}
				
					//if (m_attribute & mesh_attribute_normal) {
					//	uint32_t offset = i * 3;
					//
					//	for (uint32_t j = 0; j < 3; ++j)
					//		*data_cursor++ = normal [offset++];
					//}

					if (m_attribute & mesh_attribute_bone_index) {
						uint32_t offset = i * 2;

						for (uint32_t j = 0; j < 2; ++j) {
							*((uint32_t *)data_cursor) = bone_index [offset++];
							data_cursor += sizeof (uint32_t);
						}
					}

					if (m_attribute & mesh_attribute_bone_weight) {
						uint32_t offset = i;

						*((real *)data_cursor) = bone_weight [offset++];
						data_cursor += sizeof (real);

					}
				
				}
				
				mesh->set_data (data_buffer, buffer_size, index.data (), index.size () * sizeof (uint16_t), m_attribute, false);
				
				delete [] data_buffer;
				
				container.add_to_level (mesh);
			}

		}
	}
}