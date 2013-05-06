#include "ballistic.engine.attribute.h"
#include "ballistic.engine.entity.h"
#include "ballistic.engine.game.h"

namespace ballistic {
	namespace engine {
		
		attribute::attribute ()
		: _id (0), _parent (nullptr) {}
		
		attribute::attribute ( entity * parent, attribute::id_t id ) : _id (id), _parent (parent) {}
		
		attribute::attribute ( const attribute & orig )
		: _value (orig._value), _id (orig._id), _parent (orig._parent) {}
		
		attribute::id_t attribute::get_id () { return _id; }
		
		var attribute::get () const {
			return _value;
		}
		
		void attribute::set ( const var & v ) {
			_value = v;
			
			message m (_parent, message_attribute_changed);
			
			m [message_attribute_id] = _id;
			m [message_attribute_value] = v;
			
			_parent->get_game ()->send_message (m);
		}
		
	}
}