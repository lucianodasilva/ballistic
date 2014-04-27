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
		private:
			entity * _parent;
		public:

			template < class >
			friend class notify_property_definition;

			inline notify_property_container (entity * parent) : _parent (parent) {}

			template < class value_t >
			inline property < value_t > * require_notify (const id_t & id, const value_t & default_value) {
				auto p = this->find (id);

				if (!p) {
					auto new_p = new notify_property < value_t > (id, default_value);
					new_p->_parent = _parent;
					this->insert (new_p);
					return new_p;
				} else {
					auto typed_p = dynamic_cast < property < value_t > *> (p);

					if (!typed_p) {
						debug_print ("property " << id << " already exists with different type. property overriden.");
						delete p;

						typed_p = new notify_property < value_t > (id, default_value);
						typed_p->_parent = _parent;
						insert (typed_p);
					}

					return typed_p;
				}
			}
		};

	}
}

#endif