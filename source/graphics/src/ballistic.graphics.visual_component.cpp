#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.system.h"
#include "ballistic.graphics.common_id.h"

#include <Ballistic.h>
#include <glm.hpp>
#include <functional>

using namespace std;
using namespace glm;

namespace ballistic {
	namespace graphics {

		void visual_component::setup () {
			// Reserve properties

			entity & ent = get_entity ();

			ent [graphics::id::mesh];
			ent [graphics::id::material];
		}
		
		void visual_component::notify ( ballistic::message & message ) {
		
			if (message.get_id () != graphics::id::message_render)
				return;
			
			system * v_system = message [graphics::id::render_system];
			entity & ent = get_entity ();

			v_system->add_render_item (
				ent [graphics::id::mesh].as <irenderable *>(),
				ent [ballistic::id::transform].as <mat4>(),
				ent [graphics::id::material].as < material * > ()
			);
			
		}
		
	}
}