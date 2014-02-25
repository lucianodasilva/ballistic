#include "ballistic.message_notifier.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	message_notifier::message_notifier (entity * container) : _container (container) {}

	message_notifier::~message_notifier () {}

	void message_notifier::register_local (id_t message_id, imessage_listener * listener) {
		_listeners [message_id].push_back (listener);
	}

	void message_notifier::register_global (id_t message_id, imessage_listener * listener) {
		_container->game ()->global_notifier
	}

	void message_notifier::notify (entity * sender, message & m) {
		auto message_listeners = _listeners [m.id ()];

		for (auto listener : message_listeners)
			listener->notify (sender, m);
	}

}