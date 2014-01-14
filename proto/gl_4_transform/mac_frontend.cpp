#include "mac_frontend.h"

#ifndef _WIN32

#include <GLUT/GLUT.h>

void frontend::update_frame(){
	glutSwapBuffers();
	glutPostRedisplay ();
	_callback ();
}

frontend::frontend ( int width, int height ) : _window_width (width), _window_height (height)
{}

frontend::~frontend () {}

bool frontend::create () {
	int			dummy_c = 0;
	char *		dummy_v;
			
	glutInit ( &dummy_c, &dummy_v );
	glutInitDisplayMode  (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE );
	glutInitWindowSize(_window_width, _window_height);
	return true;
}

void frontend::show () {
	glutCreateWindow("Ballistic Mac Frontend!");
}

void frontend::destroy () {
}
		
void frontend::update () {
			
}

void frontend::do_event_loop (update_callback callback) {
	_callback = callback;
	glutDisplayFunc(update_frame);
	glutMainLoop ();
}

#endif