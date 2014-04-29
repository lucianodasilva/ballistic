
#ifndef _ballistic_notify_property_h_
#define _ballistic_notify_property_h_

#include "ballistic.property.h"
#include "ballistic.message_notifier.h"

#include "ballistic.common_id.h"

namespace ballistic {

	class entity;

	template < class >
	class notify_property_definition;

	namespace containers {
		class notify_property_container;
	}

	template < class value_t >
	class notify_property : public property < value_t > {
	protected:
		
		entity * _parent;

	public:

		friend class containers::notify_property_container;
		friend class notify_property_definition < value_t >;

		inline notify_property (const id_t & id_v, const value_t & v)
			: property < value_t > (id_v, v) {}

		inline virtual void operator = (const value_t & v) override;

		inline virtual iproperty * clone () const override;

	};
	
}

#ifndef _ballistic_entity_h_
#include "ballistic.entity.h"

namespace ballistic {
	
	// special case include to avoid circular dependencies

	template < class value_t >
	void notify_property < value_t >::operator = (const value_t & v) {
		this->_value = v;
	
		message m (id::message::property_changed);
		m.require (id::id, this->_id);
	
		_parent->local_notifier.notify (_parent, m);
	}

	template < class value_t >
	iproperty * notify_property < value_t >::clone () const {
		auto p = new notify_property < value_t > (this->_id, this->_value);
		p->_parent = _parent;
		return p;
	}
}

#endif

	// -------------------------------

#endif
