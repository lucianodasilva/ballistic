#include "ballistic.graphics.visual.h"
#include "ballistic.graphics.device.h"
#include "ballistic.graphics.common_id.h"

#include <Ballistic.h>
#include <glm.hpp>
#include <functional>

using namespace std;
using namespace glm;

namespace ballistic {
	namespace graphics {

		void visual::setup () {
			// Reserve properties

			entity & ent = get_entity ();

			ent [graphics::id::mesh];
			ent [graphics::id::material];
		}
		
		void visual::notify ( ballistic::message & message ) {
		
			if (message.get_id () != graphics::id::message_render)
				return;
			
			device * visual_device = message [graphics::id::render_device];
			entity & ent = get_entity ();

			visual_device->add_render_item (
				ent [graphics::id::mesh].as <irenderable *>(),
				ent [ballistic::id::transform].as <mat4>(),
				ent [graphics::id::material].as < material * > ()
			);
			
		}
		
	}
}