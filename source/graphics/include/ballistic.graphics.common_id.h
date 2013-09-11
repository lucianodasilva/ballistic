#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {
		namespace id {

			const id_t graphics_device					= string_to_id ("graphics_device");

			const id_t system_component					= string_to_id ("system_component");
			const id_t visual_component					= string_to_id ("visual_component");

			const id_t material							= string_to_id ("material");
			const id_t mesh								= string_to_id ("mesh");
			// -------------------
			const id_t effect_diffuse					= string_to_id ("effect_diffuse");
			const id_t effect_specular					= string_to_id ("effect_specular");
			const id_t effect_t_world					= string_to_id ("effect_t_world");
			const id_t effect_t_view					= string_to_id ("effect_t_view");

			// -------------------
			const id_t message_render					= string_to_id ("message_render");
		}
	}
}

#endif //!_ballistic_graphics_common_id_h_
