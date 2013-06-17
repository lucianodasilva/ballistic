#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.entity.h"
#include "ballistic.ifrontend.h"
#include "ballistic.message.h"

#include <functional>
#include <map>
#include <queue>
#include <string>

using namespace std;

namespace ballistic {

	class game : public entity {
	private:

		typedef map < id_t, entity * > entity_map_t;
		entity_map_t _entity_map;

		bool _running;

		void		add_entity ( entity * ent );

	public:

		entity &	create_entity ( const string & name );
		entity &	create_entity ( id_t type );

		entity &	find_entity ( id_t id );

		virtual void send_message ( ballistic::message & message );

		virtual void on_initialize ();

		virtual void do_loop (ifrontend * frontend = nullptr, function < void ( game * )> system_callback = nullptr);

		virtual void terminate ();

		game ();
		virtual ~game ();

	};
}

#endif