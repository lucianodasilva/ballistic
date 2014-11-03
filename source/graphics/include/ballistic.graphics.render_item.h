#ifndef	_ballistic_graphics_object_h_
#define _ballistic_graphics_object_h_

#include <ballistic.base.h>

#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class irenderable;
		class material;
		struct rig_frame_tween;

		typedef uint32_t render_bucket;

		struct render_item {

			irenderable *		renderable;
			material *			material;
			mat4				transform;
			rig_frame_tween *	rig;

			uint8_t			layer;

			render_bucket	bucket;

			render_item ();

			static void set_render_bucket (render_item & item, camera * camera, uint32_t offset );

		};


	}
}

#endif