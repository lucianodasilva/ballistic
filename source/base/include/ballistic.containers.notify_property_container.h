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

			using property_container::require;
			
			entity * parent;

			template < class >
			friend class notify_property_definition;

			inline notify_property_container (entity * p) : parent (p) {}

			template < class value_t >
			inline notify_property_container & require_notify (const id_t & id, const value_t & default_value, notify_property < value_t > *& p) {
				auto fp = this->find (id);

				if (!fp) {
					p = new notify_property < value_t > (id, default_value);
					p->parent = parent;
					this->insert (p);
				} else {
					p = dynamic_cast < property < value_t > *> (fp);

					if (!p) {
						debug_print ("property " << id << " already exists with different type. property overriden.");
						delete p;

						p = new notify_property < value_t > (id, default_value);
						p->parent = parent;
						insert (p);
					}
				}

				return *this;
			}

			template < class value_t >
			inline notify_property_container & require_notify (const id_t & id, const value_t & default_value) {
				notify_property < value_t > * p = nullptr;
				return require_notify (id, default_value, p);
			}
		};

	}
}

#endif