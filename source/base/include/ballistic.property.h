#ifndef	_ballistic_property_h_
#define _ballistic_property_h_

#include "ballistic.id.h"
#include "ballistic.var.h"

#include <map>

using namespace std;

namespace ballistic {

	class iproperty_container;

	class property {
	private:

		var						_value;
		id_t					_id;
		iproperty_container *	_container;

		inline void raise_property_changed_event ();

	public:

		inline property ();
		inline property (id_t id);
		inline property (iproperty_container * container, id_t id);
		inline property (const property & v);

		inline operator var () const;

		template < class T >
		inline operator T () const;

		template < class T >
		inline T as () const;

		template < class T >
		inline property & operator = (const T & v);

		inline property & operator = (const property & v);

		inline id_t get_id () const;

		inline iproperty_container * get_container () const;
		inline void set_container (iproperty_container * container);

	};

	class iproperty_container {
	public:

		virtual void property_changed_event (const property & p);

		virtual property & add_property (id_t id, const var & v) = 0;

		virtual bool has_property (id_t id) = 0;

		virtual property & get_property (id_t id) = 0;

#ifdef BALLISTIC_DEBUG
		virtual inline bool has_property (const string & name) {
			return this->has_property (string_to_id (name));
		}

		virtual inline property & get_property (const string & name) {
			return this->get_property (string_to_id (name));
		}
#endif // BALLISTIC_DEBUG 

	};

}

#include "ballistic.property.inl"

#endif