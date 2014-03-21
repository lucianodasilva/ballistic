
#ifndef _ballistic_property_h_
#define _ballistic_property_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"
#include "ballistic.debug.h"
#include "ballistic.id.h"

#include <type_traits>

#include <tinyxml2.h>

namespace ballistic {

	class entity;

	class iproperty {
	protected:

		id_t							p_id = 0;
		entity *						p_container;

	public:

		id_t							id () const;
		entity *						container () const;

		iproperty ();
		iproperty (id_t id_v, entity * container_v);

		virtual							~iproperty ();
		virtual void					raise_event () const;

		virtual bool					parse (const tinyxml2::XMLAttribute * value) = 0;
		virtual iproperty *				clone () const = 0;
	};

	namespace details {

		template < 
			class value_t, 
			bool is_fundamental = std::is_fundamental < value_t >::value, 
			bool is_pointer = std::is_pointer < value_t >::value 
		>
		struct property_parser {

			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				try {
					ret = convert_to < value_t > (value->Value ());
					return true;
				} catch (...) {
					return false;
				}
			}

		};

		template < class value_t >
		struct property_parser < value_t, false, false > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				return value_t::parse (value, ret);
			}
		};

		template < >
		struct property_parser < id_t, std::is_fundamental < id_t >::value, false > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, id_t & ret) {
				try {
					ret = text_to_id (value->Value());
					return true;
				} catch (...) {
					return false;
				}
			}
		};

		template < >
		struct property_parser < string, false, false > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, string & ret) {
				try {
					ret = value->Value ();
					return true;
				} catch (...) {
					return false;
				}
			}
		};

		template < class value_t, bool is_fundamental >
		struct property_parser < value_t, is_fundamental, true > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				debug_print ("pointer type value cannot be parsed");
				return false;
			}
		};

	}

	template < class value_t >
	class property : public iproperty {
	protected:		
		value_t					p_value;
	public:

		inline property (const id_t & id_v, const value_t & v, entity * ctner)
			: iproperty (id_v, ctner), p_value (v)
		{}

		inline void operator = (const value_t & v) {
			p_value = v;

			if (iproperty::p_container)
				iproperty::raise_event ();
		}

		inline operator value_t () const {
			return p_value;
		}

		inline virtual bool parse (const tinyxml2::XMLAttribute * config_value) override {
			bool ret = details::property_parser < value_t >::parse (config_value, p_value);

			if (!ret)
				debug_print ("unexpected data type for property " << p_id);

			return ret;
		}

		inline virtual iproperty * clone () const override {
			return new property < value_t > (iproperty::p_id, p_value, iproperty::p_container);
		}

	};

	namespace details {

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
							debug_print ("wrong type property assign for" << id);
						} else {
							debug_print ("property " << id << " not found");
						}
					);
				}
			}

			template < class value_t >
			inline value_t as () const {
#ifdef BALLISTIC_DEBUG
				auto p = dynamic_cast < property < value_t > * > (prop);
#else
				auto p = static_cast < property < value_t > * > (prop);
#endif
				if (p)
					return *p;
				else {
					debug_run (
						if (prop) {
							debug_print ("wrong type property access for" << id);
						} else {
							debug_print ("property " << id << " not found");
						}
					);
					return value_t ();
				}
			}

			template < class value_t >
			inline operator value_t () const {
				return as < value_t > ();
			}
		};
	}
}

#endif
