#ifndef _ballistic_message_notifier_h_
#define _ballistic_message_notifier_h_

#include "ballistic.id.h"
#include "ballistic.message.h"

#include <functional>
#include <map>
#include <vector>

using namespace std;

namespace ballistic {

	class entity;

	class imessage_listener {
	public:
		virtual void notify (entity * sender, message & m ) = 0;
	};

	class message_notifier {
	private:

		entity *										_container;
		map < id_t, vector < imessage_listener * > >	_listeners;

	public:

		message_notifier (const message_notifier & o) = delete;
		message_notifier & operator = (const message_notifier & o) = delete;

		message_notifier (entity * container);
		virtual ~message_notifier ();

		void attach (id_t message_id, imessage_listener * listener);
		void detach (id_t message_id, imessage_listener * listener);

		virtual void notify (message & m);
		virtual void notify (entity * sender, message & m);

	};
}

#endif
