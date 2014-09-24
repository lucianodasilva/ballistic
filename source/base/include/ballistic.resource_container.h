//
//  ballistic.resourcestack.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_resource_container_h_
#define _ballistic_resource_container_h_

#include "ballistic.debug.h"
#include "ballistic.id.h"
#include "ballistic.iresource.h"
#include "ballistic.res_id.h"

#include <string>
#include <map>
#include <list>
#include <vector>

namespace ballistic {

	namespace io {
		class iloader;
		class istorage;

		class package_loader;
	}

	namespace details {

		struct resource_auto_caster {

			template < class T >
			struct fix_pointer {
				typedef T * type;
			};

			template < class T >
			struct fix_pointer < T * > {
				typedef T * type;
			};

			iresource * res;

			inline resource_auto_caster (iresource * res_inst) : res (res_inst) {} 

			template < class T >
			inline typename fix_pointer < T >::type as () const {

				typename fix_pointer < T >::type typed_instance = nullptr;

				if (res) {

#ifdef BALLISTIC_DEBUG 
					typed_instance = dynamic_cast < typename fix_pointer < T >::type > (res);

					if (!typed_instance) {
						debug_print ("unsuported resource cast");
					}
#else
					typed_instance = static_cast < typename fix_pointer < T >::type > (res);
#endif
				}

				return typed_instance;
			}

			template < class T >
			inline operator T () const {
				return as < T > ();
			}

		};

	}
		
	class resource_container {
	private:
		
		typedef std::map < id_t, iresource * >
			resource_map_t;
			
		typedef std::vector < id_t >
			resource_id_vector_t;
		
		typedef std::vector < io::istorage * >
			storage_vector_t;
		
		typedef std::vector < io::iloader * >
			loader_vector_t;
			
		// -----------
		
		storage_vector_t
			_storage_handlers;
			
		loader_vector_t
			_loaders;
			
		resource_map_t
			_resources;
		
		vector < resource_id_vector_t >
			_stacked_resources;
			
		io::package_loader * _package_loader;
		
	public:

		io::package_loader * package_loader ();
		
		resource_container ();
		virtual ~resource_container ();
		
		void register_storage ( io::istorage * storage );
			
		io::istorage * find_storage ( const string & source );
		
		void register_loader ( io::iloader * loader );
		
		void push_level ();
		bool pop_level ();
		
		// -------------
			
		resource_container & add_to_global (iresource * resource);
			
		resource_container & add_to_level (iresource * resource);
			
		// -------------
			
		iresource * get_resource ( id_t id );
			
		template < class T >
		inline T * get_resource ( id_t id );
			
		iresource * get_resource ( const res_id_t & res_id );
		
		template < class T >
		inline T * get_resource ( const res_id_t & res_id );
			
		inline details::resource_auto_caster operator [] ( const res_id_t & res_id );

		inline details::resource_auto_caster operator [] (const id_t & id);
			
	};
		
	template < class T >
	T * resource_container::get_resource ( id_t id ) {
		return dynamic_cast <T *> ( get_resource(id) );
	}

	template < class T >
	T * resource_container::get_resource (const res_id_t & id) {
		return dynamic_cast <T *> (get_resource (id));
	}

	details::resource_auto_caster resource_container::operator [] (const res_id_t & res_id) {
		return details::resource_auto_caster (get_resource (res_id));
	}

	details::resource_auto_caster resource_container::operator [] (const id_t & id) {
		return details::resource_auto_caster (get_resource (id));
	}
		
		
}

#endif
