#ifndef	_ballistic_property_container_h_
#define _ballistic_property_container_h_

#include "ballistic.property.h"

#include <map>

namespace ballistic {

	class property_container {
	private:
		std::map < id_t, iproperty * >	_properties;
		entity *						_container;
	public:

		// delete copy and assignment
		property_container (const property_container & o) = delete;
		property_container & operator = (const property_container & o) = delete;

		typedef std::map < id_t, iproperty * >::iterator iterator;

		property_container ();
		property_container (entity * container);

		virtual ~property_container ();

		virtual void remove ( id_t id );
		virtual bool contains ( id_t id ) const;

		iterator begin ();
		iterator end ();

		template < class value_t >
		inline property < value_t > * require (const id_t & id, const value_t & default_value) {
			iterator it = _properties.find (id);

			if (it == _properties.end ()) {
				auto prop = new property < value_t > (id, default_value, _container);
				_properties [id] = prop;
				return prop;
			} else {
				auto prop = dynamic_cast <property < value_t > *> (it->second);

				if (!prop) {
					debug_print ("property " << id << " already exists with different type. property overriden.");
					delete it->second;
					prop = new property < value_t > (id, default_value, _container);
					it->second = prop;
				}
				return prop;
			}
		}

		inline details::property_accessor operator [](id_t id) {
			return details::property_accessor (id, _properties [id]);
		}

	};

}

#endif