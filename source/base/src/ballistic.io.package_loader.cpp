#include "ballistic.io.package_loader.h"

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.entity_type_reader.h"
#include "ballistic.io.package_reader.h"

#include <cpptoml.h>
using namespace cpptoml;

namespace ballistic {
	namespace io {

		ipackage_group_reader::~ipackage_group_reader () {}

		bool package_loader::handles (const string & name) {
			if (name.size () < 5)
				return false;

			return name.compare (name.size () - 5, 5, ".toml") == 0;
		}

		package_loader::package_loader () {
			register_reader (new package_reader ());
			register_reader (new entity_type_reader ());
		}

		void package_loader::register_reader (ballistic::io::ipackage_group_reader * reader) {
			_registered_types [reader->type ()] = reader;
		}

		bool package_loader::load (istream & source, uint32_t length, ballistic::resource_container & container)
		{
			try {
			
				parser document_parser (source);
				auto base_group = document_parser.parse();
			
				for (auto it : base_group) {
				
					// if element other than group
					if (!it.second->is_group()) {
						debug_print ("unexpected toml file element \"" << it.first << "\"");
						continue;
					}
					
					auto it_group = base_group.get_group(it.first);
					
					if (!it_group->contains("type")) {
						debug_print ("group \"" << it.first << "\" has no defined type");
						continue;
					}
					
					string group_type = *it_group->get_as< string >("type");
					
					// search for appropriate reader
					reader_map_t::iterator reader_it = _registered_types.find (group_type);
					
					if (reader_it == _registered_types.end ()) {
						debug_print ("type \"" << group_type << "\" for group \"" << it.first << "\" has no defined reader" );
						continue;
					}
					
					reader_it->second->load_group(it.first, *it_group, container);
				
				}
				
			} catch (const cpptoml::toml_parse_exception & e) {
				debug_print ("failed parsing toml file with exception \"" << e.what() << "\"");
				return false;
			}
			
			return true;
		}
	}
}