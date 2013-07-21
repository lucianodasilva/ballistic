//
//  ballistic.resource.package_loader.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/18/13.
//
//

#ifndef _ballistic_resource_package_loader_h_
#define _ballistic_resource_package_loader_h_

#include "ballistic.resources.iloader.h"
#include "ballistic.resources.stack.h"
#include <tinyxml2.h>

#include <map>

namespace ballistic {
	namespace resources {
		
		class package_loader : public iloader {
		public:
			
			class itype {
			public:
				
				virtual string get_name () = 0;
				
				virtual void load_element (tinyxml2::XMLElement * element, ballistic::resources::stack & stack) = 0;
				
				virtual ~itype ();
				
			};
			
			typedef map < string, itype * > type_map_t;
			
		private:
			
			type_map_t _registered_types;

		public:
			
			package_loader ();
			
			void register_type ( itype * type_inst );
			
			virtual bool handles ( const string & name );
			
			virtual bool load ( istream & source, uint32 length, ballistic::resources::stack & stack );
			
		};
		
	}
}

#endif
