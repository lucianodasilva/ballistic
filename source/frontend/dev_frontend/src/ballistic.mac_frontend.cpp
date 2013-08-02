#include "ballistic.mac_frontend.h"

#ifdef BALLISTIC_MACOSX

#include <GLUT/GLUT.h>

namespace ballistic {
	namespace mac_desktop {
		
		ballistic::game * frontend::_game;
		
		void frontend::update_frame(){
			_game->frame ();
			glutSwapBuffers();
			glutPostRedisplay ();
		}

		point frontend::get_client_size () { return _window_client_size; }

		frontend::frontend (const point & client_size ) : _window_client_size (client_size) {
		}

		frontend::~frontend () {}

		bool frontend::create () {
			int			dummy_c = 0;
			char *		dummy_v;
			
			glutInit ( &dummy_c, &dummy_v );
			glutInitDisplayMode  (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowSize(_window_client_size.x, _window_client_size.y);
			return true;
		}

		void frontend::show () {
			glutCreateWindow("Ballistic Mac Frontend!");
		}

		void frontend::destroy () {
		}
		
		void frontend::update ( ballistic::game * game ) {
			
		}

		void frontend::do_event_loop ( ballistic::game * game ) {
			_game = game;
			
			glutDisplayFunc(update_frame);
			glutMainLoop ();
		}

	}
}
#endif