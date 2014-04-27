#ifndef _property_container_h_
#define _property_container_h_

#include "property.h"

#include <map>

template < class property_interface_t >
class iproperty_container {
protected:
	std::map < id_t, property_interface_t * > data;
public:

	inline void insert (property_interface_t * prop) {
		auto it = data.find (prop->id ());

		if (it == data.end ()) 
			data [prop->id ()] = prop;
	}

	inline property_interface_t * find (const id_t & id) {
		auto it = data.find (id);

		if (it == data.end ())
			return nullptr;
		else
			return it->second;
	}

};

namespace containers {

	template < 
		class property_interface_t,
		template < class > class default_property_t
	>
	class property_container : public iproperty_container < property_interface_t > {
	public:

		template < class value_t >
		default_property_t < value_t > * require (const id_t & id, const value_t & default_value) {
			auto p = find (id);

			if (p) {
				auto typed_p = dynamic_cast <default_property_t < value_t > *> (p);

				if (typed_p)
					return typed_p;
				else
					return nullptr;
			} else {
				return new default_property_t < value_t > (id, default_value);
			}

		}
		
	
	};

	class entity_property_container : public property_container < iproperty, property > {
	private:

		entity * _parent;

	public:

		inline entity_property_container (entity * parent) : _parent (parent) {}

		template < class value_t >
		inline property < value_t > * require_active (const id_t & id, const value_t & default_value) {
			auto p = find (id);

			if (p) {
				auto typed_p = dynamic_cast <property < value_t > *> (p);

				if (typed_p)
					return typed_p;
				else
					return nullptr;
			} else {
				auto new_p = new entity_property < value_t > (id, default_value);
				new_p->_parent = _parent;

				return new_p;
			}

		}


	};

}

#endif