#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.entity.h"
#include "ballistic.entity_container.h"
#include "ballistic.ifrontend.h"
#include "ballistic.message_notifier.h"
#include "ballistic.resource_container.h"
#include "ballistic.system.h"
#include "ballistic.system_container.h"

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <atomic>

using namespace std;

namespace ballistic {
	
	class game : public entity {
	protected:

		bool _running;

		// game state ---
		system::ballistic_time_t
				_game_start_time,
				_frame_start;

		uint32_t	_frame_id;

		message _m_update;

		property < real >
			* _m_update_game_time,
			* _m_update_frame_time;

		property < uint32_t > 
			* _m_update_frame_count;

		ifrontend * _frontend;

	public:

		static game instance;

		message_notifier global_notifier;

		entity_container entities;

		resource_container resources;

		system_container systems;

		virtual void initialize ();

		virtual bool is_running ();

		virtual void do_loop (function < void ( game * )> system_callback = nullptr);

		virtual bool frame ();

		virtual void terminate ();

		game ();
		virtual ~game ();

		// ---------------------
		virtual ifrontend * frontend ();
		virtual void frontend (ifrontend * frontend);

	};

}

#undef MSG_NOT_COMPONENT_TYPE

#endif