
#ifndef _ballistic_property_h_
#define _ballistic_property_h_

#include "ballistic.config.h"
#include "ballistic.convert.h"
#include "ballistic.debug.h"
#include "ballistic.id.h"

#include <type_traits>

#include <tinyxml2.h>

namespace ballistic {

	namespace details {

		template < 
			class value_t, 
			bool is_fundamental = std::is_fundamental < value_t >::value, 
			bool is_enum = std::is_enum < value_t >::value,
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
		struct property_parser < value_t, false, true, false > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				try {
					ret = (value_t)convert_to < typename std::underlying_type < value_t >::type > (value->Value ());
					return true;
				} catch (...) {
					return false;
				}
			}
		};

		template < class value_t >
		struct property_parser < value_t, false, false, false > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				return value_t::parse (value, ret);
			}
		};

		template < >
		struct property_parser < id_t, std::is_fundamental < id_t >::value, false, false > {
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
		struct property_parser < string, false, false, false > {
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
		struct property_parser < value_t, is_fundamental, false, true > {
			inline static bool parse (const tinyxml2::XMLAttribute * value, value_t & ret) {
				debug_print ("pointer type value cannot be parsed");
				return false;
			}
		};

	}

	class iproperty {
	protected:
		id_t							_id;
	public:
		id_t							id () const;
		iproperty (id_t id_v);
		virtual							~iproperty ();
		virtual bool					parse (const tinyxml2::XMLAttribute * value) = 0;
		virtual iproperty *				clone () const = 0;
	};

	template < class value_t >
	class property : public iproperty{
	protected:
		value_t					_value;
	public:

		inline property (const id_t & id_v, const value_t & v)
			: iproperty (id_v), _value (v) {}

		inline virtual void operator = (const value_t & v) {
			_value = v;
		}

		inline operator value_t () const {
			return _value;
		}

		inline virtual bool parse (const tinyxml2::XMLAttribute * config_value) override {
			bool ret = details::property_parser < value_t >::parse (config_value, _value);

			if (!ret)
				debug_print ("unexpected data type for property " << _id);

			return ret;
		}

		inline virtual iproperty * clone () const override {
			return new property < value_t > (iproperty::_id, _value);
		}

	};

	namespace details {

		template < class base_property_t, template < class > class default_property_t >
		struct property_accessor {

			base_property_t *		property;

			inline property_accessor (base_property_t * p) : property (p) {}

			template < class value_t >
			inline void operator = (const value_t & v) {
#ifdef BALLISTIC_DEBUG
				auto p = dynamic_cast <default_property_t < value_t > *> (property);
#else
				auto p = static_cast <default_property_t < value_t > *> (property);
#endif
				if (p) {
					*p = v;
				} else {
					debug_run (
						if (property) {
							debug_print ("wrong type property assign for" << property->id ());
						} else {
							debug_print ("property not found");
						}
					);
				}
			}

			template < class value_t >
			inline value_t as () const {
#ifdef BALLISTIC_DEBUG
				auto p = dynamic_cast < default_property_t < value_t > * > (property);
#else
				auto p = static_cast < default_property_t < value_t > * > (property);
#endif
				if (p)
					return *p;
				else {
					debug_run (
						if (property) {
							debug_print ("wrong type property access for" << property->id ());
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
