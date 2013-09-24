#ifndef	_ballistic_igame_h_
#define _ballistic_igame_h_

#include "ballistic.entity.h"
#include "ballistic.ifrontend.h"
#include "ballistic.message.h"

#include "ballistic.resources.stack.h"

#include <functional>

namespace ballistic {

	class ifrontend;
	class isystem;
	
	class igame : public entity {
	public:
		
		igame ();

		virtual id_t create_id_key () = 0;
		
		// resource handling
	
		virtual resources::iresource * get_resource (const res_id_t & res_id) = 0;
		virtual resources::iresource * get_resource (id_t res_id) = 0;
		
		virtual void push_resource_level () = 0;
		virtual bool pop_resource_level () = 0;
		
		virtual resources::stack & get_resource_stack () = 0;
		
		template < class T >
		inline T * get_resource (const res_id_t & res_id);
		
		template < class T >
		inline T * get_resource (id_t res_id);

		// -----------------

		virtual void add_entity (entity * ent) = 0;

		virtual entity * find_entity ( id_t id ) = 0;

		// -----------------

		virtual void add_system (isystem * system) = 0;

		virtual isystem * find_system (id_t id) = 0;

		// -----------------

		virtual void send_message ( ballistic::message & message ) = 0;

		virtual void initialize () = 0;

		virtual bool is_running () = 0;

		virtual void do_loop (ifrontend * frontend = nullptr, function < void ( igame * )> system_callback = nullptr) = 0;

		virtual bool frame () = 0;

		virtual void terminate () = 0;

	};
	
	template < class T >
	T * igame::get_resource (const res_id_t & id) {
		return dynamic_cast <T *> (get_resource (id));
	}
	
	template < class T >
	T * igame::get_resource (id_t id) {
		return dynamic_cast <T *> (get_resource (id));
	}

}

#endif