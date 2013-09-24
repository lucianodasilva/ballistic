#ifndef _ballistic_isystem_h_
#define _ballistic_isystem_h_

#include "ballistic.id.h"
#include "ballistic.message.h"

namespace ballistic {

	class igame;

	class isystem {
	private:

		ballistic::igame * _game;

	public:

		virtual ~isystem ();

		virtual id_t get_id () = 0;

		virtual ballistic::igame * get_game ();
		virtual void set_game (ballistic::igame * value);

		virtual void notify ( ballistic::message & message ) = 0;

	};

}

#endif // !_ballistic_isystem_h_
