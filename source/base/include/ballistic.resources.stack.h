//
//  ballistic.resourcestack.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resources_stack_h_
#define _ballistic_resources_stack_h_

#include "ballistic.resources.id.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.id.h"

#include <string>
#include <map>
#include <list>
#include <vector>


namespace ballistic {
	namespace resources {
	
		class iloader;
		class istorage;
		
		class package_loader;
		
		class stack {
		private:
		
			typedef std::map < id_t, iresource * >
				resource_map_t;
			
			typedef std::vector < id_t >
				resource_id_vector_t;
		
			typedef std::vector < istorage * >
				storage_vector_t;
		
			typedef std::vector < iloader * >
				loader_vector_t;
			
			// -----------
		
			storage_vector_t
				_storage_handlers;
			
			loader_vector_t
				_loaders;
			
			resource_map_t
				_resources;
		
			list < resource_id_vector_t >
				_stacked_resources;
			
			package_loader * _package_loader;
		
		public:
		
			stack ();
			virtual ~stack ();
		
			void register_storage ( istorage * storage );
			
			istorage * find_storage ( const string & source );
			
			package_loader * get_package_loader ();
		
			void register_loader ( iloader * loader );
		
			void push ();
			bool pop ();
		
			// -------------
			
			stack & add_to_global ( id_t res_id, iresource * resource);
			
			stack & add_to_global ( const string & name, iresource * resource);
			
			stack & add_to_level ( id_t res_id, iresource * resource );
			
			stack & add_to_level ( const string & name, iresource * resource);
			
			// -------------
			
			iresource * get_resource ( id_t id );
			
			template < class T >
			inline T * get_resource ( id_t id );
			
			iresource * get_resource ( const res_id_t & res_id );
		
			template < class T >
			inline T * get_resource ( const res_id_t & res_id );
		
			iresource * operator [] ( const res_id_t & res_id );

			iresource * operator [] (id_t id);
			
			template < class T >
			inline T * operator [] ( const res_id_t & res_id );
			
		};
		
		template < class T >
		T * stack::get_resource ( id_t id ) {
			return dynamic_cast <T *> ( get_resource(id) );
		}
		
		template < class T >
		T * stack::operator [] ( const res_id_t & res_id ) {
			return get_resource <T> (res_id);
		}
		
	}
}

#endif
