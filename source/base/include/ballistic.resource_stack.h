//
//  ballistic.resourcestack.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resource_stack_h_
#define _ballistic_resource_stack_h_

#include "ballistic.resources.iloader.h"
#include "ballistic.resources.istorage.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.id.h"

#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

namespace ballistic {
	
	class resource_stack {
	private:
		
		typedef map < string, resources::iresource * >	resource_map_t;
		
		typedef vector < resources::istorage * >		storage_vector_t;
		
		typedef vector < resources::iloader * >			loader_vector_t;
		
		storage_vector_t								_storage_handlers;
		loader_vector_t									_loaders;
		
		struct resource_stack_layer {
			
			resource_map_t resources;
			
			void clear ();
			
			virtual ~resource_stack_layer ();
			
		};
		
		resource_stack_layer			_global_resources;
		list < resource_stack_layer >	_stacked_resources;
		
	public:
		
		virtual ~resource_stack ();
		
		void register_storage ( resources::istorage * storage );
		
		void register_loader ( resources::iloader * loader );
		
		void push ();
		bool pop ();
		
		resources::iresource * get_resource ( const string & name );
		
		template < class T >
		inline T * get_resource ( const string & name );
		
	};
	
	template < class T >
	T * resource_stack::get_resource(const string &name) {
		return dynamic_cast<T *>(get_resource (name));
	}
	
}

#endif
