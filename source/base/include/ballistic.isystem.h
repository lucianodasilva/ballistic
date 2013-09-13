#ifndef _ballistic_isystem_h_
#define _ballistic_isystem_h_

#include "ballistic.id.h"
#include "ballistic.message.h"

namespace ballistic {

	class game;

	class isystem {
	private:

		ballistic::game * _game;

	public:

		virtual ~isystem ();

		virtual id_t get_id () = 0;

		virtual ballistic::game * get_game ();
		virtual void set_game (ballistic::game * value);

		virtual void notify ( ballistic::message & message ) = 0;

	};

}

#endif // !_ballistic_isystem_h_
