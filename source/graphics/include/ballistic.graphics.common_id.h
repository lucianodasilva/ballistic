#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace id {

		define_id (position);
		define_id (target);
		define_id (up);

		namespace graphics {

			// default res
			define_id_ext (mesh_quad_one, graphics.mesh_quad_one);

			// camera stuffs
			define_id (left);
			define_id (right);
			define_id (top);
			define_id (bottom);
			define_id (near);
			define_id (far);
			define_id (fov);
			define_id (projection);

			// systems and components
			define_id_ext (device, graphics.device);
			define_id_ext (system,  graphics.system);

			define_id_ext (visual, graphics.visual);

			define_id_ext (overlay, graphics.overlay);
			define_id_ext (overlay_text, graphics.overlay_text);

			define_id_ext (camera, graphics.camera);

			define_id_ext (camera_view, graphics.camera_view);
			define_id_ext (camera_proj, graphics.camera_proj);

			define_id_ext (layer, graphics.layer);

			// effect 
			namespace effect {

				define_id_ext (diffuse, effect_diffuse);
				define_id_ext (texture, effect_texture);

				define_id_ext (t_model, effect_t_model);
				define_id_ext (t_view, effect_t_view);
				define_id_ext (t_normal, effect_t_normal);
				define_id_ext (t_proj, effect_t_proj);
				define_id_ext(t_mvp, effect_t_mvp);

				namespace type {
					define_id_ext(basic, effect_type.basic);
					define_id_ext(rigged, effect_type.rigged);
				}

			}

			define_id_ext (material_id, graphics.material.id);
			define_id_ext (mesh_id, graphics.mesh.id);
			define_id_ext (rig_id, graphics.rig.id);

			define_id (material);
			define_id (mesh);
			define_id (rig);

			namespace text {

				define_id_ext (text, text.text);
				define_id_ext (font, text.font);

				define_id_ext (font_id, text.font.id);

			}

		}

		namespace message {
			define_id_ext (render, message.render);
			define_id_ext (render_overlay, message.render_overlay);
		}

	}
}

#endif //!_ballistic_graphics_common_id_h_
