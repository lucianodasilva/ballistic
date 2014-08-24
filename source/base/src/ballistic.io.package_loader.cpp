#include "ballistic.io.package_loader.h"

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.animation_storyboard_reader.h"
#include "ballistic.io.entity_type_reader.h"
#include "ballistic.io.package_reader.h"

#include <tinyxml2.h>

using namespace tinyxml2;

namespace ballistic {
	namespace io {

		ipackage_group_reader::~ipackage_group_reader () {}

		bool package_loader::handles (const string & name) {
			if (name.size () < 4)
				return false;

			return name.compare (name.size () - 4, 4, ".xml") == 0;
		}

		package_loader::package_loader () {
			register_reader (new package_reader ());
			register_reader (new entity_type_reader ());
			register_reader (new animation_storyboard_reader ());
		}

		void package_loader::register_reader (ballistic::io::ipackage_group_reader * reader) {
			_registered_types [reader->type ()] = reader;
		}

		bool package_loader::load (istream & source, uint32_t length, ballistic::resource_container & container, const id_t & id)
		{
			XMLDocument document;

			if (document.LoadStream (source, length)) {
				debug_error ("failed to load xml package file");
				return false;
			}

			auto root = document.FirstChildElement ("package");

			if (!root) {
				debug_error ("failed to find \"package\" root node in package xml file");
				return false;
			}

			XMLElement * cursor = root->FirstChildElement ();
			while (cursor) {
				reader_map_t::iterator it = _registered_types.find (cursor->Name ());

				if (it != _registered_types.end ())
					it->second->load_element (cursor, container);
				debug_run (
				else
				debug_print ("unregistered element type \"" << cursor->Name () << "\" found in package.");
				);

				cursor = cursor->NextSiblingElement ();
			}

			return true;
		}
	}
}