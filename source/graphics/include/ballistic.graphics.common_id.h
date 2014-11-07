#ifndef _ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace id {

		namespace frontend {
			define_id_ext (client_size, frontend.client_size);
		}

		namespace message {
			define_id_ext (render, message.render);
			define_id_ext (start_rig_animation, message.start_rig_animation);
			define_id_ext (stop_rig_animation, message.stop_rig_animation);
			define_id_ext (client_size_changed, message.client_size_changed);
		}

		namespace camera {
			define_id_ext (id, camera);

			// properties
			define_id_ext (view, camera.view);
			define_id_ext (proj, camera.projection);

			// parameters
			define_id (left);
			define_id (right);
			define_id (top);
			define_id (bottom);
			define_id (near);
			define_id (far);
			define_id (fov);
			define_id (projection);
		}

		namespace light {
			define_id_ext (id, light);

			define_id_ext (color, light.color);
			define_id_ext (fallout, light.fallout);
			define_id_ext (intensity, light.intensity);
			define_id_ext (position, light.position);
		}

		namespace overlay {
			define_id_ext (id, overlay);
		}

		namespace overlay_text {
			define_id_ext (id, overlay_text);

			define_id_ext (text, overlay_text.text);
			define_id_ext (font, overlay_text.font);

			define_id_ext (font_id, overlay_text.font_id);
		}

		namespace rig {
			define_id_ext (id, rig);
		}

		namespace rigged {
			define_id_ext (id, rigged);
			define_id_ext (rig, rigged.rig);
			define_id_ext (rig_id, rigged.rig_id);
			define_id_ext (rig_tween, rigged.rig_tween);
		}

		namespace visual {
			define_id_ext (id, visual);

			define_id_ext (material_id, visual.material_id);
			define_id_ext (mesh_id, visual.mesh_id);

			define_id_ext (material, visual.material);
			define_id_ext (mesh, visual.mesh);

			define_id_ext (rig_id, visual.rig_id);
			define_id_ext (rig_tween, visual.rig_tween);

			define_id_ext (layer, visual.layer);
		}

		namespace graphics {
			// default res
			define_id_ext (mesh_quad_one, graphics.mesh_quad_one);

			// systems and components
			define_id_ext (device, graphics.device);
			define_id_ext (system,  graphics.system);
		}

		// effect 
		namespace effect {

			define_id_ext (diffuse, effect_diffuse);
			define_id_ext (color_mask, effect_color_mask);
			define_id_ext (ambient_sky, effect_ambient_sky);
			define_id_ext (ambient_ground, effect_ambient_ground);
			define_id_ext (ambient_intensity, effect_ambient_intensity);
			define_id_ext (specular_hardness, effect_specular_hardness);
			define_id_ext (specular_intensity, effect_specular_intensity);
			define_id_ext (opacity, effect_opacity);
			define_id_ext (texture, effect_texture);

			define_id_ext (t_eye, effect_t_eye);
			define_id_ext (t_model, effect_t_model);
			define_id_ext (t_view, effect_t_view);
			define_id_ext (t_normal, effect_t_normal);
			define_id_ext (t_proj, effect_t_proj);
			define_id_ext (t_mvp, effect_t_mvp);

			define_id_ext (bone_count, effect_bone_count);
			define_id_ext (t_bones, effect_t_bones);

			define_id_ext (light_count, effect_light_count);
			define_id_ext (lights, effect_lights [0]);

			namespace type {
				define_id_ext (basic, effect_type.basic);
				define_id_ext (rigged, effect_type.rigged);
			}

		}
	}
}

#endif //!_ballistic_graphics_common_id_h_
