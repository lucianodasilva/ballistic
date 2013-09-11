#ifndef	_ballistic_property_container_h_
#define _ballistic_property_container_h_

#include "ballistic.property.h"

namespace ballistic {

	class property_container : public iproperty_container {
	private:

		property_map_t	_property_map;

	public:

		virtual ~property_container ();

		virtual void property_changed_event (const property & p);

		virtual property & add_property (id_t id, const var & v);

		virtual bool has_property (id_t id);

		virtual property & get_property (id_t id);

	};

}

#endif