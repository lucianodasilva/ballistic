#include "ballistic.message_notifier.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	message_notifier::message_notifier (entity * container) : _container (container) {}

	message_notifier::~message_notifier () {}
	
	void message_notifier::attach (id_t message_id, imessage_listener * listener) {
		_listeners [message_id].push_back (listener);
	}
	
	void message_notifier::detach (id_t message_id, imessage_listener * listener) {
		vector < imessage_listener * > & listener_list = _listeners [message_id];
		
		auto it = std::find (
			listener_list.begin (),
			listener_list.end (),
			listener
		);
		
		if (it != listener_list.end ())
			listener_list.erase (it);
	}

	void message_notifier::notify (entity * sender, message & m) {
		auto message_listeners = _listeners [m.id ()];

		for (auto listener : message_listeners)
			listener->notify (sender, m);
	}

}