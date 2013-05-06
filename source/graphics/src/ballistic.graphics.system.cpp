#include "ballistic.graphics.system.h"
#include "ballistic.graphics.defines.h"

namespace ballistic {
	namespace graphics {

		void system::set_entity ( engine::entity * ent ) {
			_message_inst = engine::message (ent, message_render_frame);
			engine::icomponent::set_entity (ent);
		}

		system::system () : _message_inst (nullptr, message_render_frame), _render_items (100) {
		}

		void system::add_render_item ( irenderable * renderable, const mat4 & transform ) {
			_render_items.push_back (render_item (renderable, transform));
		}
		
		void system::notify(ballistic::engine::message &message) {
			
			if (message.get_id() == engine::message_update) {
				
				_render_items.clear ();

				glClear (GL_COLOR_BUFFER_BIT);
				glMatrixMode(GL_MODELVIEW);

				// signal renderables that the show is about to start
				get_entity ()->get_game ()->send_message (_message_inst);
				
				int32 length = _render_items.size ();
				for (int32 i = 0; i < length; ++i) {
					render_item & item = _render_items [i];

					glLoadMatrixf (&item.transform[0][0]);
					irenderable * render_object = _render_items [i].render_object;

					render_object->render();
				}

			}
			
		}
		
	}
}