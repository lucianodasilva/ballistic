#include "ballistic.game.h"

#include "ballistic.debug.h"
#include "ballistic.common_id.h"
#include "ballistic.system.h"

#include "ballistic.animation.h"

#include <functional>

namespace ballistic {

	game game::instance;

	void game::initialize () {
		_frame_start = _game_start_time = system::get_time_now ();
		_frame_id = 1;
		_running = true;

		_m_update.require < real > (id::game_time, .0);
		_m_update.require < real > (id::frame_time, .0);
		_m_update.require < uint32_t > (id::frame_count, 0);

		// default resources and others
		animation::define_resources ();

		message m (this, id::message_initialize);
		global_notifier.notify (m);
	}

	bool game::is_running () { return _running; }

	void game::do_loop (function < void ( game * ) > system_callback) {

		if (!_frontend) {
			debug_error ("[ballistic::game::do_loop] frontend not set!")
		}

		while (frame ()){
			if (system_callback)
				system_callback (this);

			_frontend->update ();
		}
	}

	bool game::frame () {
		
		_m_update [id::game_time] =	system::get_elapsed_seconds (_game_start_time);
		_m_update [id::frame_time] = system::get_elapsed_seconds (_frame_start);
		_m_update [id::frame_count] = _frame_id;

		// do something with this
		// real average_fps = real (_frame_id) / system::get_elapsed_seconds (_game_start_time);

		_frame_start = system::get_time_now ();

		global_notifier.notify (_m_update);

		// clean up dead entities
		entities.execute_death_row ();

		_frame_id++;

		return _running;
	}

	void game::terminate () {
		message m (this, id::message_terminate);
		// add message properties here

		global_notifier.notify (m);
		_running = false;
	}

	game::game () :
		entity (0, nullptr), 
		_m_update (this, id::message_update), 
		_frontend (nullptr),
		global_notifier (this),
		entities (this)
	{}

	game::~game () {}

	void game::frontend (ifrontend * fend) {
		_frontend = fend;
	}

	ifrontend * game::frontend () {
		return _frontend;
	}
}