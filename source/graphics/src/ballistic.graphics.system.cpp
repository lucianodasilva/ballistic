#include "ballistic.graphics.system.h"
#include "ballistic.graphics.defines.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		void system::set_entity ( entity * ent ) {
			_message_inst = message (ent, id::message_render);
			_message_inst [id::render_system] = this;

			icomponent::set_entity (ent);
		}

		system::system () : _message_inst (nullptr, id::message_render), _render_items (100) {
		}

		void system::add_render_item ( irenderable * renderable, const mat4 & transform, graphics::material * mat ) {
			if (renderable && mat)
				_render_items.push_back (render_item (renderable, transform, mat));
		}
		
		void system::notify(ballistic::message &message) {
			
			if (message.get_id() == ballistic::id::message_update) {
				
				_render_items.clear ();

				glClearColor (0.0F, 0.75F, 1.0F, 1.0F); // Clear black
				glClear (GL_COLOR_BUFFER_BIT);
				
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-10, 10, 10, -10, 10, -10);
				
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				// signal renderables that the show is about to start
				get_entity ().get_game ()->send_message (_message_inst);
				
				int32 length = _render_items.size ();
				for (int32 i = 0; i < length; ++i) {
					glPushMatrix();
					render_item & item = _render_items [i];

					item.material->activate ();

					glLoadMatrixf (&item.transform[0][0]);
					irenderable * render_object = _render_items [i].render_object;
					render_object->render();

					item.material->deactivate ();
					glPopMatrix();
				}

			}
			
		}
		
	}
}