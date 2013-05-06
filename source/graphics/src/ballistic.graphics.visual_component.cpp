#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.system.h"

namespace ballistic {
	namespace graphics {
		
		void visual_component::notify ( ballistic::engine::message & message ) {
		
			if (message.get_id () != message_render_frame)
				return;
			
			system * v_system = message [message_render_frame_system];
			
		}
		
	}
}