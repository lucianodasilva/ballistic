#include "ballistic.entity.h"

namespace ballistic {
		
	id_t entity::id () { return _id; }
		
	entity::entity (id_t id_v) : 
		_id (id_v),
		properties (this),
		local_notifier (this)
	{}

}