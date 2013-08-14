#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		namespace id {

			const id_t system_component					= string_to_id ("system_component");

			const id_t material							= string_to_id ("material");
			const id_t mesh								= string_to_id ("mesh");
			// -------------------
			const id_t material_diffuse					= string_to_id ("material_diffuse");
			const id_t material_specular				= string_to_id ("material_specular");

			// -------------------
			const id_t message_render					= string_to_id ("message_render");
		}
	}
}

#endif //!_ballistic_graphics_common_id_h_
