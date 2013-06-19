
#include <ballistic.base.h>
#include <ballistic.graphics.opengl.h>
#include "ballistic.mac_desktop.frontend.h"

#include <GLUT/GLUT.h>

ballistic::game *   				_game;
ballistic::mac_desktop::frontend *	_frontend;
ballistic::graphics::opengl_device * _device;

void update () {
	_device->start_frame ();
	_game->frame (_frontend);
	_device->end_frame();
	glutSwapBuffers();
}

int main ( int argc, char ** argv) {

	glutInit ( &argc, argv );
	
	_frontend = new ballistic::mac_desktop::frontend (point ( 1024, 700 ));
	_frontend->create ();
	_frontend->show ();
	
	glutDisplayFunc (update);
	
	_game = new ballistic::game ();
	_game->on_initialize ();
	
	_device = new ballistic::graphics::opengl_device ();
	
	glClearColor(.0, .8, 1, 1);
	glutMainLoop();
	
	return 0;
}