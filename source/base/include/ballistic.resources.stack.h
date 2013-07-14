//
//  ballistic.resourcestack.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_stack_h_
#define _ballistic_resources_stack_h_

#include "ballistic.resources.iloader.h"
#include "ballistic.resources.istorage.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.id.h"

#include <string>
#include <map>
#include <list>
#include <vector>


namespace ballistic {
	namespace resources {
	
		class stack {
		private:
		
			typedef std::map < string, iresource * >	resource_map_t;
		
			typedef std::vector < istorage * >		storage_vector_t;
		
			typedef std::vector < iloader * >			loader_vector_t;
		
			storage_vector_t								_storage_handlers;
			loader_vector_t									_loaders;
		
			struct layer {
			
				resource_map_t resources;
			
				void clear ();
			
				virtual ~layer ();
			
			};
		
			layer			_global_resources;
			list < layer >	_stacked_resources;
		
		public:
		
			stack ();
			virtual ~stack ();
		
			void register_storage ( istorage * storage );
		
			void register_loader ( iloader * loader );
		
			void push ();
			bool pop ();
		
			iresource * get_resource ( const string & name );
		
			template < class T >
			inline T * get_resource ( const string & name );
		
		};
	
		template < class T >
		T * stack::get_resource(const string &name) {
			return dynamic_cast<T *>(get_resource (name));
		}
	}
}

#endif
