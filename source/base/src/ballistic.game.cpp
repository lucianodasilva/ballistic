#include "ballistic.game.h"

#include "ballistic.common_id.h"
#include "ballistic.entity_factory.h"
#include "ballistic.system.h"

#include <functional>

namespace ballistic {

	void game::add_entity ( entity * ent ) {
		_entity_map [ent->get_id ()] = ent;
		ent->set_game (this);
	}

	entity & game::create_entity ( const string & name ) {
		return create_entity (hash < string > ()(name));
	}

	entity & game::create_entity ( id_t type ) {
		entity * new_entity = entity_factory::create (type);

		add_entity (new_entity);
		return *new_entity;
	}

	entity & game::find_entity ( id_t id ) {
		if (_entity_map.find (id) == _entity_map.end ())
			throw "Entity not found in entity map";

		return *_entity_map [id];
	}

	void game::send_message ( ballistic::message & message ) {
		entity_map_t::iterator
			it = _entity_map.begin (),
			end = _entity_map.end ();

		for (; it != end; ++it) {
			it->second->notify (message);
		}
	}

	void game::on_initialize () {

		_frame_start = _game_start_time = system::get_time_now ();
		_frame_id = 1;
		_running = true;

		message m (this, id::message_initialize);
		send_message (m);
	}

	void game::do_loop (ifrontend * frontend, function < void ( game * ) > system_callback) {
		on_initialize ();

		while (
			frame (frontend, system_callback)
		){}
	}

	bool game::frame (ifrontend * frontend, function < void ( game * ) > system_callback ) {
		
		_m_update [id::game_time] = system::get_elapsed_seconds (_game_start_time);
		_m_update [id::frame_time] = system::get_elapsed_seconds (_frame_start);
		_m_update [id::frame_count] = _frame_id;

		_frame_start = system::get_time_now ();

		send_message (_m_update);

		if (system_callback)
			system_callback (this);

		if (frontend)
			frontend->update (this);

		_frame_id++;

		return _running;
	}

	void game::terminate () {
		message m (this, id::message_terminate);
		// add message attributes here

		send_message (m);
		_running = false;
	}

	game::game () : entity (0), _m_update (this, id::message_update) {
		set_game (this);
		_entity_map [this->get_id ()] = this;
	}

	game::~game () {
		entity_map_t::iterator
			it = _entity_map.begin (),
			end = _entity_map.end ();
			
		for (; it != end; ++it) {
			if (it->second->get_id () != 0)
				delete it->second;
		}
	}
}