
#ifndef _ballistic_property_h_
#define _ballistic_property_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"
#include "ballistic.id.h"

namespace ballistic {

	class iproperty;

	class iproperty_container {
	public:
		virtual void property_changed_event (iproperty * changed_property) = 0;
	};

	class iproperty {
	public:
		virtual id_t					id () = 0;
		virtual iproperty_container *	container () = 0;
		virtual							~iproperty ();
	};

	template < class value_t >
	class property : public iproperty {
	private:
		id_t					_id;		
		value_t					_value;
		iproperty_container *	_container;
	public:

		inline virtual id_t						id () { return _id; }
		inline virtual iproperty_container *	container () { return _container; }

		inline property (const id_t & id_v, const value_t & v, iproperty_container * ctner)
			: _id (id_v), _value (v), _container (ctner)
		{}

		inline void operator = (const value_t & v) {
			_value = v;
			_container->property_changed_event (this);
		}

		inline operator value_t () const {
			return _value;
		}

	};

	namespace details {

		class null_property_container : public iproperty_container {
		public:
			static null_property_container static_instance;

			virtual void property_changed_event (iproperty * changed_property);
		};

		struct property_accessor {

			id_t			id;
			iproperty *		prop;

			inline property_accessor (const id_t & id_v, iproperty * p) : id (id_v), prop (p) {}

			template < class value_t >
			inline void operator = (const value_t & v) {
#ifdef BALLISTIC_DEBUG
				auto p = dynamic_cast <property < value_t > *> (prop);
#else
				auto p = static_cast <property < value_t > *> (prop);
#endif
				if (p) {
					*p = v;
				} else {
					debug_run (
						if (prop) {
							debug_print ("[base::property_accessor::assign] wrong type property assign for" << id);
						} else {
							debug_print ("[base::property_accessor::assign] property " << id << " not found");
						}
					);
				}
			}

			template < class value_t >
			inline operator value_t () const {
#ifdef BALLISTIC_DEBUG
				auto p = dynamic_cast <property < value_t > *> (prop);
#else
				auto p = static_cast <property < value_t, > *> (prop);
#endif
				if (p)
					return *p;
				else {
					debug_run (
						if (prop) {
							debug_print ("[base::property_accessor::access] wrong type property access for" << id);
						} else {
							debug_print ("[base::property_accessor::access] property " << id << " not found");
						}
					);
					return value_t ();
				}
			}
		};
	}
}

#endif
