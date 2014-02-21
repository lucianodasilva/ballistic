#ifndef	_ballistic_property_container_h_
#define _ballistic_property_container_h_

#include "ballistic.property.h"

#include <map>

namespace ballistic {

	class property_map {
	private:
		std::map < id_t, iproperty * >	_properties;
		iproperty_container *			_container;
	public:

		typedef std::map < id_t, iproperty * >::iterator iterator;

		property_map ();
		property_map (iproperty_container * container);

		virtual ~property_map ();

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
					debug_print ("[base::property_map::require] Property " << id << " already exists with different type. Property overwriten.");
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