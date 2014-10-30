#ifndef	_ballistic_property_definition_container_h_
#define _ballistic_property_definition_container_h_

#include "ballistic.property.h"
#include "ballistic.notify_property.h"
#include "ballistic.containers.property_container.h"
#include "ballistic.containers.notify_property_container.h"

#include <map>

namespace ballistic {

	class iproperty_definition : public iproperty {
	public:

		inline iproperty_definition (const id_t & id_v) : iproperty (id_v) {}

		virtual void insert_property (containers::iproperty_container < iproperty > & container) = 0;

	};

	template < class value_t >
	class property_definition : public iproperty_definition {
	protected:
		value_t					_value;
	public:

		inline property_definition (const id_t & id_v, const value_t & v)
			: iproperty_definition (id_v), _value (v) {}

		inline virtual void operator = (const value_t & v) {
			_value = v;
		}

		inline operator value_t () const {
			return _value;
		}

		inline virtual bool parse (const tinyxml2::XMLAttribute * config_value) override {
			bool ret = details::property_parser < value_t >::parse (config_value, _value);

			if (!ret)
				debug_print ("unexpected data type for property definition " << _id);

			return ret;
		}

		inline virtual iproperty * clone () const override {
			return new property_definition < value_t > (_id, _value);
		}

		inline virtual void insert_property (containers::iproperty_container < iproperty > & container) {
			container.insert (new property < value_t > (_id, _value));
		}

	};

	template < class value_t >												
	class notify_property_definition : public property_definition < value_t > {
	public:

		inline notify_property_definition (const id_t & id_v, const value_t & v)
			: property_definition < value_t > (id_v, v) {}

		inline virtual iproperty * clone () const override {
			return new notify_property_definition < value_t > (this->_id, this->_value);
		}

		inline virtual void insert_property (containers::iproperty_container < iproperty > & container) {
			auto notify_c = dynamic_cast <containers::notify_property_container *> (&container);

			if (!notify_c) {
				debug_print ("container cannot support notifications for property " << this->_id);
				container.insert (new property < value_t > (this->_id, this->_value));
			} else {
				auto p = new notify_property < value_t > (this->_id, this->_value);
				p->parent = notify_c->parent;

				notify_c->insert (p);
			}
		}

	};

	namespace containers {

		class property_definition_container : public ballistic::containers::base_property_container < iproperty_definition, property_definition > {
		public:

			using this_type = property_definition_container;

			using base_t = ballistic::containers::base_property_container < iproperty_definition, property_definition > ;
			using base_t::require;

			template < class value_t >
			inline property_definition_container & require_notify (const id_t & id, const value_t & default_value, notify_property_definition < value_t > *& p) {
				auto fp = this->find (id);

				if (!fp) {
					p = new notify_property_definition < value_t > (id, default_value);
					this->insert (p);
				} else {
					p = dynamic_cast < notify_property_definition < value_t > *> (fp);

					if (!p) {
						debug_print ("property " << id << " already exists with different type. property overriden.");
						delete p;

						p = new notify_property_definition < value_t > (id, default_value);
						insert (p);
					}
				}

				return *this;
			}

			template < class value_t >
			inline property_definition_container & require_notify (const id_t & id, const value_t & default_value) {
				notify_property_definition < value_t > * p = nullptr;
				return require_notify (id, default_value, p);
			}

			template < class value_t >
			inline property_definition_container & require_notify (const id_t & id) {
				return require_notify (id, value_t ());
			}

			inline void setup_container (iproperty_container < iproperty > & container) {

				for (auto it : data) {
					it.second->insert_property (container);
				}

			}

		};

	}
}

#endif