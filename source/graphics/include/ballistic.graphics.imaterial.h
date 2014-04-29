#ifndef	_ballistic_graphics_imaterial_h_
#define _ballistic_graphics_imaterial_h_

#include <ballistic.base.h>

#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {

		class itexture;
		class ieffect;

		class idevice;

		class imaterial_property : public iproperty {
		public:

			inline imaterial_property (const id_t & id) : iproperty (id) {}

			virtual void apply () = 0;

		};

		template < class value_t >
		class material_property : public imaterial_property {
		protected:
			value_t		_value;
			iconstant * _constant;
		public:

			inline material_property (const id_t & id_v, const value_t & v, iconstant * constant)
				: imaterial_property (id_v), _value (v), _constant (constant) {}

			inline void operator = (const value_t & v) {
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
				return new material_property < value_t > (imaterial_property::_id, _value, _constant);
			}

			inline virtual void apply () override {
				_constant->set_value (_value);
			}
		};

		namespace containers {

			class material_property_container : public ballistic::containers::base_property_container < imaterial_property, material_property > {

				inline void apply () {
					for (auto it : data)
						it.second->apply ();
				}

			};

		}

		class imaterial : public ballistic::iresource {
		public:

			imaterial (const id_t & id);

			virtual void		effect (ieffect * effect) = 0;
			virtual ieffect *	effect () = 0;

			virtual void		diffuse (const color & v) = 0;
			virtual color		diffuse () = 0;

			virtual void		specular (const color & v) = 0;
			virtual color		specular () = 0;

			virtual void		opaque (bool v) = 0;
			virtual bool		opaque () = 0;

			virtual void		texture (itexture * v) = 0;
			virtual itexture *	texture () = 0;

			containers::material_property_container properties;

			virtual void		apply (idevice * device) = 0;

		};

	}
}

#endif