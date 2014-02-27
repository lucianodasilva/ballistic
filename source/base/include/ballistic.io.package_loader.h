//
//  ballistic.resource.package_loader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#ifndef _ballistic_io_package_loader_h_
#define _ballistic_io_package_loader_h_

#include "ballistic.io.iloader.h"
#include <tinyxml2.h>

#include <map>

namespace ballistic {
	namespace io {

		class ipackage_element_reader {
		public:

			virtual const char * name () const = 0;

			virtual void load_element (tinyxml2::XMLElement * element, ballistic::resource_container & container) = 0;

			virtual ~ipackage_element_reader ();

		};

		class package_loader : public iloader {
		public:

			typedef map < string, ipackage_element_reader * > reader_map_t;

		private:

			reader_map_t _registered_types;

		public:

			package_loader ();

			void register_reader (ipackage_element_reader * reader);

			virtual bool handles (const string & name);

			virtual bool load (istream & source, uint32_t length, ballistic::resource_container & container);

			static istream & get_line (istream & stream, string & trim, char delimiter);

		};
	}	
}

#endif
