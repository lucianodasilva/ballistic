#ifndef _ballistic_isystem_h_
#define _ballistic_isystem_h_

#include "ballistic.id.h"
#include "ballistic.message_notifier.h"

namespace ballistic {

	class game;

	class isystem : public imessage_listener {
	private:

		ballistic::game & _game;

	public:

		isystem (ballistic::game & game_ref);
		virtual ~isystem ();

		virtual id_t id () = 0;

		virtual void attach () = 0;
		virtual void detach () = 0;

		inline ballistic::game & game () { return _game; }

	};

}

#endif // !_ballistic_isystem_h_
