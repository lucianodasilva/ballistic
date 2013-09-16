#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace id {

		const id_t target	= string_to_id ("target");
		const id_t up		= string_to_id ("up");

		namespace graphics {

			// camera stuffs
			const id_t left = string_to_id ("left");
			const id_t right = string_to_id ("right");
			const id_t top = string_to_id ("top");
			const id_t bottom = string_to_id ("bottom");
			const id_t near = string_to_id ("neat");
			const id_t far = string_to_id ("far");
			const id_t projection = string_to_id ("projection");

			const id_t device = string_to_id ("graphics::device");
			const id_t system = string_to_id ("graphics::system");

			const id_t visual = string_to_id ("graphics::visual");
			const id_t camera = string_to_id ("graphics::camera");

			namespace effect {
				const id_t diffuse	= string_to_id ("effect_diffuse");
				const id_t specular = string_to_id ("effect_specular");
				const id_t t_world	= string_to_id ("effect_t_world");
				const id_t t_view	= string_to_id ("effect_t_view");
				const id_t t_proj	= string_to_id ("effect_t_proj");
			}
		}
		
		const id_t material	= string_to_id ("material");
		const id_t mesh	= string_to_id ("mesh");

		const id_t message_render = string_to_id ("message_render");

	}
}

#endif //!_ballistic_graphics_common_id_h_
