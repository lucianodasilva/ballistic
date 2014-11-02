#include "ballistic.game.h"

#include "ballistic.debug.h"
#include "ballistic.common_id.h"
#include "ballistic.system.h"

#include "ballistic.animation.h"
#include "ballistic.transformed.h"

#include <functional>

namespace ballistic {

	void game::initialize () {
		_frame_start = _game_start_time = system::get_time_now ();
		_frame_id = 1;
		_running = true;

		_m_update
			.require < real > (id::game::game_time, .0, _m_update_game_time)
			.require < real > (id::game::frame_time, .0, _m_update_frame_time)
			.require < uint32_t > (id::game::frame_count, 0, _m_update_frame_count);

		// default resources and others
		animation::define_resources (*this);

		// define base components
		ballistic::component::declare < transformed > (*this);

		message m (this, id::message::initialize);
		global_notifier.notify (m);
	}

	bool game::is_running () { return _running; }

	//void game::do_loop (function < void ( game * ) > system_callback) {
	//
	//	if (!_frontend) {
	//		debug_error ("[ballistic::game::do_loop] frontend not set!")
	//	}
	//
	//	while (frame ()){
	//		if (system_callback)
	//			system_callback (this);
	//
	//		_frontend->update ();
	//	}
	//}

	bool game::frame () {
		
		*_m_update_game_time =	system::get_elapsed_seconds (_game_start_time);
		*_m_update_frame_time = system::get_elapsed_seconds (_frame_start);
		*_m_update_frame_count = _frame_id;

		// execute entity creations
		entities.execute_creates ();

		// do something with this
		// real average_fps = real (_frame_id) / system::get_elapsed_seconds (_game_start_time);

		_frame_start = system::get_time_now ();

		global_notifier.notify (_m_update);

		// clean up dead entities
		entities.execute_kills();

		_frame_id++;

		return _running;
	}

	void game::terminate () {
		message m (this, id::message::terminate);
		// add message properties here

		global_notifier.notify (m);
		_running = false;
	}

	game::game () :
		entity (*this, 0, nullptr), 
		_m_update (this, id::message::update),
		global_notifier (this),
		entities (*this),
		systems (),
		resources ()
	{}

	game::~game () {}

}