#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.resources.component_constructor.h"
#include "ballistic.entity.h"
#include "ballistic.ifrontend.h"
#include "ballistic.isystem.h"
#include "ballistic.message.h"
#include "ballistic.system.h"


#include "ballistic.resources.stack.h"

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <atomic>

using namespace std;

namespace ballistic {
	
	class game : public entity {
	protected:
		
		// entity id
		atomic<unsigned int> _id_key;

		typedef map < id_t, entity * > entity_map_t;
		entity_map_t _entity_map;

		typedef vector < isystem * > system_list_t;
		system_list_t _systems;

		bool _running;

		// game state ---
		system::ballistic_time_t
				_game_start_time,
				_frame_start;

		uint32	_frame_id;
		message _m_update;
		
		// internal systems
		resources::stack _resources;

	public:

		virtual id_t create_id_key ();
		
		// resource handling
	
		virtual resources::iresource * get_resource (const res_id_t & res_id);
		virtual resources::iresource * get_resource (id_t res_id);

		template < class T >
		inline T * get_resource (const res_id_t & res_id);

		template < class T >
		inline T * get_resource (id_t res_id);
		
		virtual void push_resource_level ();
		virtual bool pop_resource_level ();
		
		virtual resources::stack & get_resource_stack ();

		// -----------------

		virtual void add_entity (entity * ent);

		virtual entity * find_entity ( id_t id );

		// -----------------

		virtual void add_system (isystem * system);

		virtual isystem * find_system (id_t id);

		// -----------------

		virtual void send_message ( ballistic::message & message );

		virtual void initialize ();

		virtual bool is_running ();

		virtual void do_loop (ifrontend * frontend = nullptr, function < void ( game * )> system_callback = nullptr);

		virtual bool frame ();

		virtual void terminate ();

		game ();
		virtual ~game ();

	};

	template < class T >
	T * game::get_resource (const res_id_t & id) {
		return dynamic_cast <T *> (get_resource (id));
	}

	template < class T >
	T * game::get_resource (id_t id) {
		return dynamic_cast <T *> (get_resource (id));
	}

}

#undef MSG_NOT_COMPONENT_TYPE

#endif