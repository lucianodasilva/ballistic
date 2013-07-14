#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.entity.h"
#include "ballistic.ifrontend.h"
#include "ballistic.message.h"
#include "ballistic.system.h"

#include "ballistic.resources.stack.h"

#include <functional>
#include <map>
#include <queue>
#include <string>


using namespace std;

namespace ballistic {

	class game : public entity {
	protected:

		typedef map < id_t, entity * > entity_map_t;
		entity_map_t _entity_map;

		bool _running;

		void		add_entity ( entity * ent );

		// game state ---
		system::ballistic_time_t
				_game_start_time,
				_frame_start;

		uint32	_frame_id;
		message _m_update;
		
		// internal systems
		resources::stack _resources;

	public:
		
		resources::stack & get_resources ();

		entity &	create_entity ( const string & name );
		entity &	create_entity ( id_t type );

		entity &	find_entity ( id_t id );

		virtual void send_message ( ballistic::message & message );

		virtual void on_initialize ();

		virtual bool is_running ();

		virtual void do_loop (ifrontend * frontend = nullptr, function < void ( game * )> system_callback = nullptr);

		virtual bool frame ();

		virtual void terminate ();

		game ();
		virtual ~game ();

	};
}

#endif