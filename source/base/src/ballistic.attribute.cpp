#include "ballistic.attribute.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"
#include "ballistic.common_id.h"

namespace ballistic {
	attribute::attribute () : _id (0), _parent (nullptr) {}

	attribute::attribute ( entity * parent, id_t id ) : _id (id), _parent (parent) {}
		
	attribute::attribute ( const attribute & orig )
	: _value (orig._value), _id (orig._id), _parent (orig._parent) {}
		
	id_t attribute::get_id () { return _id; }
		
	void attribute::raise_changed_event ( ) {
		if (_parent) {
			message m (_parent, id::message_attribute_changed);
			
			m [id::id] = _id;
			m [id::value] = _value;
			
			_parent->get_game ()->send_message (m);
		}
	}
}