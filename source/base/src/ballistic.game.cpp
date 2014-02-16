#include "ballistic.game.h"

#include "ballistic.debug.h"
#include "ballistic.common_id.h"
#include "ballistic.resources.entity_info.h"
#include "ballistic.system.h"

#include <functional>

namespace ballistic {

	id_t game::create_id_key () {
		return std::hash < unsigned int > ()(++_id_key);
	}

	void game::add_entity ( entity * ent ) {
		_entity_map [ent->get_id ()] = ent;
		ent->set_game (this);
	}
	
	// resource handling -------
	
	resources::iresource * game::get_resource(const ballistic::res_id_t &res_id)	{
		return _resources [res_id];
	}

	resources::iresource * game::get_resource (id_t id) {
		return _resources.get_resource (id);
	}
	
	void game::push_resource_level() {
		_resources.push();
	}
	
	bool game::pop_resource_level() {
		return _resources.pop ();
	}
	
	resources::stack & game::get_resource_stack() { return _resources; }
	
	// -------------------------

	entity * game::find_entity ( id_t id ) {
		entity_map_t::iterator it = _entity_map.find (id);

		if (it == _entity_map.end ()) {
			debug_print ("[ballistic::game::find_entity] Entity with id: " << id << " not found in entity map");
			return nullptr;
		}

		return it->second;
	}

	// ------------------------------------

	void game::add_system (isystem * system) {

		if (!system) {
			debug_error ("[ballistic::game::add_system] System instance not set to an instance of an object. No system added.");
			return;
		}

		for (auto s : _systems) {
			if (s->get_id () == system->get_id ()) {
				debug_error ("[ballistic::game::add_system] Duplicate system id found. System not added.");
				return;
			}
		}

		_systems.push_back (system);
		system->set_game (this);
	}

	isystem * game::find_system (id_t id) {
		for (auto s : _systems) {
			if (s->get_id () == id)
				return s;
		}

		return nullptr;
	}

	// ------------------------------------

	void game::send_message ( ballistic::message & message ) {

		for (auto it : _entity_map)
			it.second->notify (message);

		for (auto * sys : _systems)
			sys->notify (message);
	}

	void game::initialize () {
		_frame_start = _game_start_time = system::get_time_now ();
		_frame_id = 1;
		_running = true;

		message m (this, id::message_initialize);
		send_message (m);
	}

	bool game::is_running () { return _running; }

	void game::do_loop (function < void ( igame * ) > system_callback) {

		if (!_frontend) {
			debug_error ("[ballistic::game::do_loop] frontend not set!")
		}

		while (frame ()){
			if (system_callback)
				system_callback (this);

			_frontend->update (this);
		}
	}

	bool game::frame () {
		
		_m_update [id::game_time] =	system::get_elapsed_seconds (_game_start_time);
		_m_update [id::frame_time] = system::get_elapsed_seconds (_frame_start);
		_m_update [id::frame_count] = _frame_id;

		_frame_start = system::get_time_now ();

		send_message (_m_update);

		_frame_id++;

		return _running;
	}

	void game::terminate () {
		message m (this, id::message_terminate);
		// add message properties here

		send_message (m);
		_running = false;
	}

	game::game () : igame (), _id_key(0), _m_update (this, id::message_update), _frontend (nullptr) {
		set_game (this);
		_entity_map [this->get_id ()] = this;
	}

	game::~game () {

		for (auto it : _entity_map)  {
			if (it.second->get_id () != 0)
				delete it.second;
		}

		for (auto sys : _systems)
			delete sys;
	}

	void game::set_frontend (ifrontend * frontend) {
		_frontend = frontend;
	}

	ifrontend * game::get_frontend () {
		return _frontend;
	}
}