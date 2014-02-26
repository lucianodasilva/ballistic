#ifndef _ballistic_isystem_h_
#define _ballistic_isystem_h_

#include "ballistic.id.h"
#include "ballistic.message_notifier.h"

namespace ballistic {

	class isystem : public imessage_listener {
	public:

		virtual ~isystem ();

		virtual id_t id () = 0;

	};

}

#endif // !_ballistic_isystem_h_
