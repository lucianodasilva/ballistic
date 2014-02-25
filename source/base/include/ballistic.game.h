#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.entity.h"
#include "ballistic.entity_container.h"
#include "ballistic.isystem.h"

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

		uint32_t	_frame_id;
		message _m_update;
		
		// internal systems
		resources::stack _resources;

		ifrontend * _frontend;

	public:

		entity_container entities;

		system_container systems;

		resource_container resources;

		id_t create_id_key ();

		virtual void send_message ( ballistic::message & message );

		virtual void initialize ();

		virtual bool is_running ();

		virtual void do_loop (function < void ( igame * )> system_callback = nullptr);

		virtual bool frame ();

		virtual void terminate ();

		game ();
		virtual ~game ();

		// ---------------------
		virtual ifrontend * get_frontend ();
		virtual void set_frontend (ifrontend * frontend);

	};

}

#undef MSG_NOT_COMPONENT_TYPE

#endif