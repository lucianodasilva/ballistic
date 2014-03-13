#ifndef _ballistic_message_h_
#define _ballistic_message_h_

#include "ballistic.id.h"
#include "ballistic.property_container.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

namespace ballistic {

	class entity;

	class message : public property_container {
	private:

		id_t				_id;
		entity *			_sender;

	public:

		inline message (id_t message_id);
		inline message ( entity * sender, id_t message_id );

		inline id_t id () const;

		inline entity * sender () const;
		inline void sender (entity * s);

	};

	message::message (id_t message_id) : _id (message_id), _sender (nullptr) {}

	message::message ( entity * sender, id_t message_id ) : _id (message_id), _sender (sender) {}

	inline id_t message::id () const { return _id; }

	inline entity * message::sender () const { return _sender; }

	inline void message::sender (entity * s) { _sender = s; }

	class inotification_target {
		virtual void notify (ballistic::message & message) = 0;
	};
}

#endif
