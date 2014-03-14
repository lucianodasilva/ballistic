#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace id {

		const id_t target	= text_to_id ("target");
		const id_t up		= text_to_id ("up");

		namespace graphics {

			// camera stuffs
			const id_t left = text_to_id ("left");
			const id_t right = text_to_id ("right");
			const id_t top = text_to_id ("top");
			const id_t bottom = text_to_id ("bottom");
			const id_t near = text_to_id ("near");
			const id_t far = text_to_id ("far");
			const id_t fov = text_to_id ("fov");
			const id_t projection = text_to_id ("projection");

			const id_t device = text_to_id ("graphics_device");
			const id_t system = text_to_id ("graphics_system");

			const id_t visual = text_to_id ("graphics_visual");
			const id_t camera = text_to_id ("graphics_camera");

			namespace effect {
				const id_t diffuse	= text_to_id ("effect_diffuse");
				const id_t specular = text_to_id ("effect_specular");
				const id_t texture	= text_to_id ("effect_texture");
				const id_t t_model	= text_to_id ("effect_t_model");
				const id_t t_view	= text_to_id ("effect_t_view");
				const id_t t_normal = text_to_id ("effect_t_normal");
				const id_t t_proj	= text_to_id ("effect_t_proj");
			}

			const id_t material_id = text_to_id ("material_id");
			const id_t mesh_id = text_to_id ("mesh_id");

			const id_t material = text_to_id ("material");
			const id_t mesh = text_to_id ("mesh");

		}

		const id_t message_render = text_to_id ("message_render");

	}
}

#endif //!_ballistic_graphics_common_id_h_
