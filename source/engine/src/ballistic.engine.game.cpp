#include "ballistic.engine.game.h"

#include "ballistic.engine.common_messages.h"
#include "ballistic.system.h"

#include <functional>

namespace ballistic {
	namespace engine {

		void game::add_entity ( entity * ent ) {
			_entity_map [ent->get_id ()] = ent;
			ent->set_game (this);
		}

		entity * game::create_entity ( const string & name ) {
			return create_entity (hash < string > ()(name));
		}

		entity * game::create_entity ( entity_type_t type ) {
			entity * new_entity = entity_factory::create (type);

			add_entity (new_entity);
			return new_entity;
		}

		void game::send_message ( ballistic::engine::message & message ) {
			entity_map_t::iterator
				it = _entity_map.begin (),
				end = _entity_map.end ();

			for (; it != end; ++it) {
				it->second->notify (message);
			}
		}

		void game::on_initialize () {
			message m (this, message_initialize);
			send_message (m);
		}

		void game::loop ( function < void ( game * ) > system_callback) {
			_running = true;

			on_initialize ();

			auto loop_start_time = system::get_time_now ();
			auto frame_start = system::get_time_now ();

			uint32 frame_id = 1;
			message m_update (this, message_update);

			while (_running) {

				// update message attributes
				m_update [message_game_time] = system::get_elapsed_seconds (loop_start_time);
				m_update [message_frame_time] = system::get_elapsed_seconds (frame_start);
				m_update [message_frame_count] = frame_id;

				frame_start = system::get_time_now ();

				send_message (m_update);

				if (system_callback)
					system_callback (this);

				frame_id++;
			}
		}

		void game::terminate () {
			message m (this, message_terminate);
			// add message attributes here

			send_message (m);
			_running = false;
		}

		game::game () : entity (0) {
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
}