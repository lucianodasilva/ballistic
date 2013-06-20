
#include <ballistic.base.h>
#include <ballistic.graphics.opengl.h>

#include "ballistic.mac_desktop.frontend.h"

#include <GLUT/GLUT.h>


ballistic::game *						_game;
ballistic::mac_desktop::frontend *		_frontend;
ballistic::graphics::opengl_device *	_device;

ballistic::graphics::imesh *			_mesh;

void update () {
	_device->clear ();
	_device->begin_frame ();
	
	glBegin(GL_TRIANGLE_STRIP);
	glColor3b(255, 0, 0);
	glVertex3f(-4., -1., .0);
	glVertex3f(-3., -1., .0);
	glVertex3f(-4., 1., .0);
	glEnd ();
	
	_mesh->attach();
	_mesh->render ();
	_mesh->detach();
	
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
	
	glViewport(0, 0, 1024, 700);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	
	_game = new ballistic::game ();
	_game->on_initialize ();
	
	_device = new ballistic::graphics::opengl_device ();
	
	_mesh = _device->create_mesh();
	
	ballistic::graphics::vertex vbuffer [4]
	= {
		{vec3 (-1, -1, 0), vec2 (0, 0)},
		{vec3 (1, -1, 0), vec2 (1, 0)},
		{vec3 (1, 1, 0), vec2 (1, 1)},
		{vec3 (-1, 1, 0), vec2 (0, 1)}
	};
	
	uint16 index [6] {
		0, 1, 3,
		3, 1, 2
	};
	
	_mesh->set_data(&vbuffer [0], 4, &index[0], 3);
	
	_device->set_clear_color(color (.0, .6, 1., 1.));
	glutMainLoop();
	
	return 0;
}