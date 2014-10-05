#ifndef _ballistic_graphics_ieffect_h_
#define	_ballistic_graphics_ieffect_h_

/*
	Supported shader keywords

	effect_diffuse
	effect_t_model
	effect_t_view
	effect_t_proj
	effect_t_mvp


*/

#include <ballistic.base.h>
#include <string>

#include "ballistic.graphics.light.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;
		class imaterial_property;

		class iconstant {
		public:

			virtual void set_value (uint32_t v) = 0;
			virtual void set_value (int32_t v) = 0;
			virtual void set_value (real v) = 0;
			virtual void set_value (const vec2 & v) = 0;
			virtual void set_value (const vec3 & v) = 0;
			virtual void set_value (const vec4 & v) = 0;
			virtual void set_value (const mat4 & v) = 0;
			virtual void set_value (const std::vector < mat4 > & v) = 0;
			virtual void set_value (const std::vector < light_info > & v) = 0;

			virtual bool is_null ();
			
			virtual ~iconstant ();

		};

		class null_constant : public iconstant {
		public:

			static null_constant instance;

			virtual void set_value (uint32_t v) override;
			virtual void set_value (int32_t v) override;
			virtual void set_value (real v) override;
			virtual void set_value (const vec2 & v) override;
			virtual void set_value (const vec3 & v) override;
			virtual void set_value (const vec4 & v) override;
			virtual void set_value (const mat4 & v) override;
			virtual void set_value (const std::vector < mat4 > & v) override;
			virtual void set_value (const std::vector < light_info > & v) override;

			virtual bool is_null () override;

		};

		class ieffect : public ballistic::iresource {
		public:

			ieffect (const id_t & id);

			virtual uint8_t run_id () = 0;

			virtual void load (
				const char * buffer,
				uint32_t length
			) = 0;

			virtual void apply (idevice * device) = 0;

			virtual iconstant * constant(const id_t & id) = 0;
			virtual const map < id_t, iconstant * > & constants () const = 0;

		};

	}
}

#endif