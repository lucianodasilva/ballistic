
#ifndef _ballistic_property_h_
#define _ballistic_property_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"
#include "ballistic.id.h"
#include <cpptoml.h>

#include <type_traits>

namespace ballistic {

	class entity;

	class iproperty {
	protected:

		id_t							_id = 0;
		entity *						_container;

	public:

		id_t							id () const;
		entity *						container () const;

		iproperty ();
		iproperty (id_t id_v, entity * container_v);

		virtual							~iproperty ();
		void							raise_event () const;

		virtual bool					parse (std::shared_ptr < cpptoml::toml_base > value) = 0;
		virtual iproperty *				clone () const = 0;
	};

	namespace details {

		template < 
			class value_t, 
			bool is_fundamental = std::is_fundamental < value_t >::value, 
			bool is_pointer = std::is_pointer < value_t >::value 
		>
		struct property_parser {

			inline static bool parse (std::shared_ptr < cpptoml::toml_base > value, value_t & ret) {
				auto typed_value = value->as < value_t > ();

				if (!typed_value)
					return false;

				ret = typed_value->value ();
				return true;
			}

		};

		template < class value_t >
		struct property_parser < value_t, false, false > {
			inline static bool parse (std::shared_ptr < cpptoml::toml_base > value, value_t & ret) {
				return value_t::parse (value, ret);
			}
		};

		template < >
		struct property_parser < id_t, std::is_fundamental < id_t >::value, false > {
			inline static bool parse (std::shared_ptr < cpptoml::toml_base > value, id_t & ret) {
				auto typed_value = value->as < string  > ();

				if (!typed_value)
					return false;

				ret = text_to_id (typed_value->value ().c_str ());
				return true;
			}
		};

		template < >
		struct property_parser < string, false, false > {
			inline static bool parse (std::shared_ptr < cpptoml::toml_base > value, string & ret) {
				auto typed_value = value->as < string  > ();

				if (!typed_value)
					return false;

				ret = typed_value->value ();
				return true;
			}
		};

		template < class value_t, bool is_fundamental >
		struct property_parser < value_t, is_fundamental, true > {
			inline static bool parse (std::shared_ptr < cpptoml::toml_base > value, value_t & ret) {
				debug_print ("pointer type value cannot be parsed");
				return false;
			}
		};

	}

	template < class value_t >
	class property : public iproperty {
	private:		
		value_t					_value;
	public:

		inline property (const id_t & id_v, const value_t & v, entity * ctner)
			: iproperty (id_v, ctner), _value (v)
		{}

		inline void operator = (const value_t & v) {
			_value = v;
			iproperty::raise_event ();
		}

		inline operator value_t () const {
			return _value;
		}

		inline value_t get () const {
			return _value;
		}

		inline virtual bool parse (std::shared_ptr < cpptoml::toml_base > config_value) {
			bool ret = details::property_parser < value_t >::parse (config_value, _value);

			if (!ret)
				debug_print ("unexpected data type for property " << id ());

			return ret;
		}

		inline virtual iproperty * clone () const {
			return new property < value_t > (id (), _value, container ());
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
				auto p = dynamic_cast <property < value_t > *> (prop);
#else
				auto p = static_cast <property < value_t, > *> (prop);
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
