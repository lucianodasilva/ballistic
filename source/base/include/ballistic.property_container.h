#ifndef	_ballistic_property_container_h_
#define _ballistic_property_container_h_

#include "ballistic.property.h"

#include <map>

namespace ballistic {

	class property_container {
	private:
		std::map < id_t, iproperty * >	_properties;
		entity *						_container;

		template < class value_t >
		inline property < value_t > * require (const id_t & id, const value_t & default_value, entity * container) {
			iterator it = _properties.find (id);

			if (it == _properties.end ()) {
				auto prop = new property < value_t > (id, default_value, container);
				_properties [id] = prop;
				return prop;
			} else {
				auto prop = dynamic_cast <property < value_t > *> (it->second);

				if (!prop) {
					debug_print ("property " << id << " already exists with different type. property overriden.");
					delete it->second;
					prop = new property < value_t > (id, default_value, container);
					it->second = prop;
				}
				return prop;
			}
		}

	public:

		// delete copy and assignment
		property_container (const property_container & o) = delete;
		property_container & operator = (const property_container & o) = delete;

		typedef std::map < id_t, iproperty * >::iterator iterator;
		typedef std::map < id_t, iproperty * >::const_iterator const_iterator;

		property_container ();
		property_container (entity * container);

		virtual ~property_container ();

		void remove ( id_t id );
		bool contains ( id_t id ) const;

		size_t count () const;

		iterator begin ();
		iterator end ();

		const_iterator cbegin () const;
		const_iterator cend () const;

		void copy_to (property_container & dest) const;

		template < class value_t >
		inline property < value_t > * require (const id_t & id, const value_t & default_value) {
			return require < value_t > (id, default_value, _container);
		}

		template < class value_t >
		inline property < value_t > * require_silent (const id_t & id, const value_t & default_value) {
			return require < value_t > (id, default_value, nullptr);
		}

		template < class value_t >
		inline property < value_t > * aquire (const id_t & id) {
			iterator it = _properties.find (id);

			if (it == _properties.end ()) {
				debug_print ("no property with id \"" << id << "\" defined");
				return new property < value_t > (id, value_t (), nullptr); // null property
			} else {
				auto prop = dynamic_cast <property < value_t > *> (it->second);

				if (!prop) {
					debug_print ("property " << id << " required with different type.");
					return new property < value_t > (id, value_t (), nullptr); // null property
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