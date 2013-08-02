#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>

#include "ballistic.graphics.opengl_mesh.h"

namespace ballistic {
	namespace graphics {
		
		opengl_device::opengl_device () : _current_mesh (nullptr) {
			glewInit ();
		}
	
		imaterial * opengl_device::create_material ()
		{
			return nullptr;
		}
		
		imesh *	opengl_device::create_mesh ()
		{
			return new opengl_mesh ();
		}
		
		itexture * opengl_device::create_texture (const point & size)
		{
			return nullptr;
		}
		
		imaterial * opengl_device::load_material ( const string & filename )
		{
			return nullptr;
		}
		
		imesh *	opengl_device::load_mesh ( const string & filename )
		{
			return nullptr;
		}
		
		itexture * opengl_device::load_texture ( const string & filename )
		{
			return nullptr;
		}
		
		void opengl_device::set_transform(const mat4 & matrix)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf (&matrix.data [0]);
		}
		
		void opengl_device::set_projection ( const mat4 & matrix ) {
			glMatrixMode(GL_PROJECTION);
			glLoadTransposeMatrixf (&matrix.data [0]);
		}

		void opengl_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void opengl_device::clear () {
			glClearColor (
				_clear_color.r,
				_clear_color.g,
				_clear_color.b,
				_clear_color.a
			);

			glClear (GL_COLOR_BUFFER_BIT);
		}

		mat4 create_ortho (real left, real right, real bottom, real top, real near, real far) {
			return mat4 ( 
				2.0 / ( right - left ), .0, .0, -((right + left)/(right - left)),
				.0, 2.0 / ( top - bottom ), .0, -((top + bottom) / ( top - bottom)),
				.0, .0, -2 / ( far - near ), - ((far + near) / ( far - near)),
				.0, .0, .0, 1.0
			);
		}
		
		void opengl_device::begin_frame ()
		{
			glClear(GL_DEPTH_BUFFER_BIT);			
		}

		void draw_line (const vec3 & v1, const vec3 & v2) {
			glBegin (GL_LINES);
			glVertex3f (v1.x, v1.y, v1.z);
			glVertex3f (v2.x, v2.y, v2.z);
			glEnd ();
		}

		void draw_joint (const vec3 & bone, const vec3 & bone_child ) {
			glColor3f (1., .0, .0);

			draw_line (bone, bone_child);

			glColor3f (.0, 1., .0);
			
			draw_line (bone + vec3 (-.01, .0, .0), bone + vec3 (.01, .0, .0));
			draw_line (bone + vec3 (0, -.01, .0), bone + vec3 (.0, .01, .0));
		}

		struct joint {
			vec3 position;
			quat attitude;
		};
		
		real angle = 0.0;
		
		void opengl_device::end_frame ()
		{
			// ----------
			joint p = {
				vec3 (0.0, .5, .0),
				quat(vec3 (1.0, 1.0, 0.0), .0)
			};

			joint j1 = {
				vec3 (0.0, -.25, .0),
				quat (vec3 (0.0, 1.0, .0), .0)
			};

			joint j2 = {
				vec3 (.0, -.25, .0),
				quat (vec3 (.0, 1.0, .0), .0)
			};

			vec3 apt = p.position;
			quat apq = math::normalize (
				quat (
					vec3 (cos (angle), sin (angle), .0),
					  0.0
				)
			);

			vec3 aj1t = apq * (apt + j1.position);
			quat aj1q = apq * j1.attitude;

			vec3 aj2t = aj1q * (aj1t + j2.position);
			quat aj2q = aj1q * j2.attitude;

			draw_joint (apt, aj1t);
			draw_joint (aj1t, aj2t);

			glFlush ();
			
			angle += 0.0005;

			// ----------
			//glFlush ();
		}
		
		void opengl_device::set_current_mesh ( imesh * mesh )
		{
			if (mesh == _current_mesh)
				return;

			if (_current_mesh)
				_current_mesh->detach ();

			_current_mesh = mesh;
			_current_mesh->attach ();
		}

		imesh * opengl_device::get_current_mesh () {
			return _current_mesh;
		}
		
		void opengl_device::set_current_texture ( itexture * texture )
		{
		
		}
		
		void opengl_device::present ()
		{
		
		}
		
		void opengl_device::destroy ()
		{
		
		}
	
	}
}