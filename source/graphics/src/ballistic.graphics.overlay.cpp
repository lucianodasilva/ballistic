#include "ballistic.graphics.overlay.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.material.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		const id_t overlay::component_id = ballistic::id::graphics::overlay;

		overlay::overlay ()
			:
			visual ()
		{}

		void overlay::notify ( entity * sender, ballistic::message & message ) {
			material * mat = *_material;
			imesh * mesh = *_mesh;

			if (!mat) {
				debug_print ("missing material instance. will not render");
				return;
			}

			if (
				_system &&
				mat &&
				mesh
			){
				_system->push_overlay_item (mat, mesh, *_layer, *_transform);
			} else {
				debug_print ("incomplete overlay component. will not render!");
			}
		}

	}
}