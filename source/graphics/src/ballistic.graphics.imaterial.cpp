#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		imaterial::imaterial (const id_t & id) : iresource (id) {}

		void imaterial::setup_defaults (imaterial * material) {
			containers::material_property_container & properties = material->properties;

			properties.require < mat4 > (id::graphics::effect::t_model);
			properties.require < mat4 > (id::graphics::effect::t_view);
			properties.require < mat4 > (id::graphics::effect::t_normal);
			properties.require < mat4 > (id::graphics::effect::t_proj);

			properties.require < uint32_t > (id::graphics::effect::texture);

		}

	}
}