#include <ballistic.base.h>

#ifdef BALLISTIC_OS_DARWIN

#include "ballistic.desktop.frontend_osx.h"

#include <GLUT/GLUT.h>

namespace ballistic {
	namespace mac_desktop {
		
		game * frontend::_game = nullptr;
		
		message frontend::_on_mouse_message (id::frontend::on_mouse_event);
		
		void frontend::update_frame(){
			_game->frame ();
			glutSwapBuffers();
			glutPostRedisplay ();
		}

		void frontend::on_mouse_button(int button, int state, int x, int y) {
		
			mouse_event_type m_event;
			
			mouse_button buttons = (mouse_button)_on_mouse_message [id::frontend::mouse_buttons].as < uint32_t > ();
		
			
			if (state == GLUT_DOWN) {
				m_event = mouse_event_down;
				
				switch (button) {
					case GLUT_LEFT_BUTTON:
						buttons = (mouse_button)(buttons | mouse_button_left);
						break;
					case GLUT_RIGHT_BUTTON:
						buttons = (mouse_button)(buttons | mouse_button_right);
						break;
					case GLUT_MIDDLE_BUTTON:
						buttons = (mouse_button)(buttons | mouse_button_middle);
						break;
					default:
						break;
				}
			} else {
				m_event = mouse_event_up;
				
				switch (button) {
					case GLUT_LEFT_BUTTON:
						buttons = (mouse_button)(buttons ^mouse_button_left);
						break;
					case GLUT_RIGHT_BUTTON:
						buttons = (mouse_button)(buttons ^ mouse_button_right);
						break;
					case GLUT_MIDDLE_BUTTON:
						buttons = (mouse_button)(buttons ^ mouse_button_middle);
						break;
					default:
						break;
				}
			}
			
			point position = {x, y};

			
			int wheel_delta = 0;

			_on_mouse_message [id::frontend::mouse_event_type] = (uint32_t)m_event;
			_on_mouse_message [id::frontend::mouse_position] = position;
			_on_mouse_message [id::frontend::mouse_buttons] = (uint32_t)buttons;
			_on_mouse_message [id::frontend::mouse_wheel_delta] = wheel_delta;
			
			_game->global_notifier.notify (_on_mouse_message);
		}
		
		void frontend::on_mouse_move(int x, int y) {
		
			mouse_event_type m_event = mouse_event_move;
			
			point position = {x, y};

			_on_mouse_message [id::frontend::mouse_event_type] = (uint32_t)m_event;
			_on_mouse_message [id::frontend::mouse_position] = position;
			
			_game->global_notifier.notify (_on_mouse_message);
		}
		
		point frontend::get_client_size () { return _window_client_size; }

		frontend::frontend (game & game_ref, const point & client_size ) :
			_window_client_size (client_size)
		{
			_on_mouse_message
				.require < point > (id::frontend::mouse_position)
				.require < uint32_t > (id::frontend::mouse_buttons)
				.require < int > (id::frontend::mouse_wheel_delta)
				.require < uint32_t > (id::frontend::mouse_event_type);
			
			_on_mouse_message [id::frontend::mouse_event_type] = (uint32_t)mouse_event_none;
			_on_mouse_message [id::frontend::mouse_position] = point {0, 0};
			_on_mouse_message [id::frontend::mouse_buttons] = (uint32_t)mouse_button_none;
			_on_mouse_message [id::frontend::mouse_wheel_delta] = 0;
			
			_game = &game_ref;
		}

		frontend::~frontend () {}

		bool frontend::create () {
			int			dummy_c = 0;
			char *		dummy_v;
			
			glutInit ( &dummy_c, &dummy_v );
			glutInitDisplayMode  (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE );
			glutInitWindowSize(_window_client_size.x, _window_client_size.y);
			return true;
		}

		void frontend::show () {
			glutCreateWindow("Ballistic Mac Frontend!");
		}

		void frontend::destroy () {
		}
		
		void frontend::update () {
			
		}

		void frontend::do_event_loop () {
			glutDisplayFunc(update_frame);
			glutMouseFunc(on_mouse_button);
			glutMotionFunc(on_mouse_move);
			glutMainLoop ();
		}

	}
}
#endif