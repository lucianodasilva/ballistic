#include "ballistic.property.h"

#include "ballistic.common_id.h"
#include "ballistic.entity.h"
#include "ballistic.game.h"

namespace ballistic {

	iproperty::iproperty (id_t id_v) : _id (id_v) {}

	id_t iproperty::id () const { return _id; }

	iproperty::~iproperty () {}

	//ientity_property::ientity_property (const id_t & id_v, entity * parent_inst) : iproperty (id_v), _parent (parent_inst) {}

	//entity * ientity_property::parent () const { return _parent; }


	//void ientity_property::raise_event () const {
	//	message m (_parent, id::message::property_changed);
	//	m [id::id] = p_id;

	//	_parent->local_notifier.notify (m);
	//}

}