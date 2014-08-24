#ifndef _ballistic_graphics_graphics_system_h_
#define	_ballistic_graphics_graphics_system_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.render_list.h"

namespace ballistic {
	namespace graphics {

		class graphics_system : public ballistic::isystem {
		private:

			idevice *	_device;
			camera	*	_camera;

			message		_render_message;

			render_list _render_list;

			ieffect *	_material_effect;

			// effect constants
			iconstant
				* _c_effect_diffuse,
				* _c_effect_texture,
				* _c_effect_t_model,
				* _c_effect_t_view,
				* _c_effect_t_proj,
				* _c_effect_t_normal,
				* _c_effect_t_mvp;

			ieffect *	_overlay_effect;

		public:

			graphics_system ();

			virtual id_t id ();

			void device (idevice * dev);
			idevice * device () const;

			void camera (ballistic::graphics::camera * cam);
			const ballistic::graphics::camera * camera () const ;

			void material_effect (ieffect * effect);
			ieffect * material_effect () const;

			void overlay_effect (ieffect * effect);
			ieffect * overlay_effect () const;

			void render ();

			virtual void notify ( entity * sender, ballistic::message & message );

			virtual void attach ();
			virtual void detach ();

			// methods
			virtual void push_item (material * material, imesh * mesh, uint8_t layer, const mat4 & transform);

		};
				  
	}
}

#endif