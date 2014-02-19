#ifndef _ballistic_message_h_
#define _ballistic_message_h_

#include "ballistic.var.h"
#include "ballistic.id.h"
#include "ballistic.property_container.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

namespace ballistic {

	class entity;

	class message : public property_map {
	private:
			
		map < id_t, var >	_properties;
		id_t				_id;
		entity *			_sender;

	public:

		inline message (id_t message_id);
		inline message ( entity * sender, id_t message_id );

		inline id_t get_id () const;

		inline entity * get_sender () const;
		inline void set_sender (entity * s);

	};

	message::message (id_t message_id) : _id (message_id), _sender (nullptr) {}

	message::message ( entity * sender, id_t message_id ) : _id (message_id), _sender (sender) {}

	inline id_t message::get_id () const { return _id; }

	inline entity * message::get_sender () const { return _sender; }

	inline void message::set_sender (entity * s) { _sender = s; }

	 
}

#endif
