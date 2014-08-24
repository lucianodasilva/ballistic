#ifndef	_ballistic_notify_property_container_h_
#define _ballistic_notify_property_container_h_

#include "ballistic.notify_property.h"
#include "ballistic.containers.property_container.h"

#include <map>

namespace ballistic {

	class entity;

	template < class >
	class notify_property_definition;

	namespace containers {

		class notify_property_container : public property_container {
		public:
			
			entity * parent;

			template < class >
			friend class notify_property_definition;

			inline notify_property_container (entity * p) : parent (p) {}

			template < class value_t >
			inline property < value_t > * require_notify (const id_t & id, const value_t & default_value) {
				auto prop = this->find (id);

				if (!prop) {
					auto new_p = new notify_property < value_t > (id, default_value);
					new_p->parent = parent;
					this->insert (new_p);
					return new_p;
				} else {
					auto typed_p = dynamic_cast < property < value_t > *> (prop);

					if (!typed_p) {
						debug_print ("property " << id << " already exists with different type. property overriden.");
						delete prop;

						typed_p = new notify_property < value_t > (id, default_value);
						typed_p->parent = parent;
						insert (typed_p);
					}

					return typed_p;
				}
			}
		};

	}
}

#endif