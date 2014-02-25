#include "ballistic.entity.h"

namespace ballistic {

	game * entity::game () { return _game; }
		
	id_t entity::id () { return _id; }
		
	entity::entity (id_t id_v) : 
		_game (nullptr), 
		_id (id_v),
		properties (this) 
	{}

}