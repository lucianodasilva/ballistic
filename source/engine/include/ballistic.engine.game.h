#ifndef	_ballistic_engine_game_h_
#define _ballistic_engine_game_h_

#include "ballistic.engine.entity.h"
#include "ballistic.engine.entity_factory.h"
#include "ballistic.engine.message.h"

#include <functional>
#include <map>
#include <queue>
#include <string>

using namespace std;

namespace ballistic {
	namespace engine {

		class game : public entity {
		private:

			typedef map < entity_id_t, entity * > entity_map_t;
			entity_map_t _entity_map;

			bool _running;

		public:

			void		add_entity ( entity * ent );
			entity *	create_entity ( const string & name );
			entity *	create_entity ( entity_type_t type );

			virtual void send_message ( ballistic::engine::message & message );

			virtual void on_initialize ();
			virtual void loop (function < void ( game * )> system_callback = nullptr);

			virtual void terminate ();

			game ();
			virtual ~game ();

		};

	}
}

#endif