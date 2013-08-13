#include "ballistic.graphics.opengl_device.h"

#include <GL/glew.h>
#include "ballistic.graphics.opengl_effect.h"
#include "ballistic.graphics.opengl_debug.h"
#include "ballistic.graphics.opengl_mesh.h"

namespace ballistic {
	namespace graphics {
		
		real
			angle = .0,
		angle_inc = .001;
	
		struct joint {
			vec3 p;
			quat r;

			inline joint () {}
			inline joint (const vec3 & vP, const quat & qR) : p (vP), r (qR) {}
			
			inline joint to_absolute ( const joint & parent ) {
				return joint (
					parent.p + (parent.r * p),
					parent.r * r
				);
				//return joint ();
			}
		};

		joint bones [] = {
			joint (
				vec3 (.0, .0, .0),
				quat::from_axis(vec3 (.0, .0, 1), .0)
			),
			joint (
				vec3 (.0, .2, .0),
				quat::from_axis(vec3 (.0, .0, 1), .0)
			),
			joint (
				vec3 (.0, .2, .0),
				quat::from_axis(vec3 (.0, .0, 1), .0)
			),
			joint (
				vec3 (.0, .2, .0),
				quat::from_axis(vec3 (.0, .0, 1), .0)
			),
			joint (
				vec3 (.0, .2, .0),
				quat::from_axis(vec3 (.0, .0, 1), .0)
			),
		};
		
		struct cvec {
			vec3	position;
			uint16	b1;
			uint16	b2;
			real	bias;
			vec4	color;
		};
		
		cvec vec_buffer [] = {
			// position				| bone 1 | bone 2 |	bone bias | color
			{vec3 (-.1, .0, .0)	    , 0		 , 1	  , .0		  , vec4 (.0, .0, 1., 1.)},
			{vec3 (.1, .0, .0)	    , 0		 , 1	  , .0		  , vec4 (.0, .0, 1., 1.)},
			{vec3 (-.1, .2, .0)	    , 0		 , 1	  , 1.0		  , vec4 (.0, .0, 1., 1.)},
			{vec3 (.1, .2, .0)	    , 0		 , 1	  , 1.0		  , vec4 (.0, .0, 1., 1.)}
		};
		
		uint16 index_buffer [] = {
			0, 1, 2,
			3, 2, 1
		};
		
		uint32
			_vertex_array_id,
			_vertex_buffer_id,
			_index_buffer_id;
		
		int32
			_in_bones_p_id,
			_in_bones_r_id
		;

		graphics::ieffect * _effect;


		opengl_device::opengl_device () : _current_mesh (nullptr) {

			glewExperimental = true;
			GLenum init_error = glewInit();
			if (init_error != GLEW_OK) {
				debug_error ("glew initialization error: " << glewGetErrorString(init_error));
			}
			
			glGetError (); // reset errors
			
			string gl_str_version = (const char *) glGetString (GL_VERSION);
			debug_print ("OpenGL version: " << gl_str_version);
			
			_vertex_buffer_id = 0;
			_index_buffer_id = 0;
			
			// Create vertex buffer
			gl_eval (glGenBuffers (1, &_vertex_buffer_id));
			gl_eval (glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id));

			uint32 vertex_buffer_size = sizeof (vec_buffer);
			gl_eval (glBufferData( GL_ARRAY_BUFFER, vertex_buffer_size, (GLvoid *)&vec_buffer [0], GL_STATIC_DRAW));
			
			// Create index buffer
			gl_eval (glGenBuffers (1, &_index_buffer_id));
			gl_eval (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id));
			gl_eval (glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (index_buffer), (GLvoid *)&index_buffer, GL_STATIC_DRAW));
			
			// unbind buffers
			gl_eval(glBindBuffer (GL_ARRAY_BUFFER, 0));
			gl_eval(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
			
			// create and setup vao
			gl_eval(glGenVertexArrays (1, &_vertex_array_id));
			gl_eval(glBindVertexArray (_vertex_array_id));
			
			gl_eval(glBindBuffer (GL_ARRAY_BUFFER, _vertex_buffer_id));
			
			// position
			gl_eval (
				glVertexAttribPointer(
				   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				   3,                  // size
				   GL_FLOAT,           // type
				   GL_FALSE,           // normalized?
				   sizeof (cvec),                  // stride
				   (void*)0            // array buffer offset
				)
			);
			gl_eval(glEnableVertexAttribArray (0));
			
			gl_eval (
				glVertexAttribPointer(
					1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					2,                  // size
					GL_UNSIGNED_SHORT,  // type
					GL_FALSE,           // normalized?
					sizeof (cvec),      // stride
					(void*)(offsetof (cvec, b1))            // array buffer offset
					)
				);
			gl_eval(glEnableVertexAttribArray (1));
			
			gl_eval (
			glVertexAttribPointer(
					2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					2,                  // size
					GL_UNSIGNED_SHORT,  // type
					GL_FALSE,           // normalized?
					sizeof (cvec),      // stride
					(void*)(offsetof (cvec, b2))            // array buffer offset
					)
			);
			gl_eval(glEnableVertexAttribArray (2));
			
			gl_eval (
					 glVertexAttribPointer(
						   3,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
						   1,                  // size
						   GL_FLOAT,  // type
						   GL_FALSE,           // normalized?
						   sizeof (cvec),      // stride
						   (void*)(offsetof (cvec, bias))            // array buffer offset
						   )
					 );
			gl_eval(glEnableVertexAttribArray (3));
			
			// color
			gl_eval (
				glVertexAttribPointer(
					4,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					4,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					sizeof (cvec),              // stride
					(void*)(offsetof (cvec, color))      // array buffer offset
				);
			);
			gl_eval(glEnableVertexAttribArray (4));
			
			gl_eval(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id));
			
			// reset state machine
			gl_eval (glBindVertexArray (0));
			//gl_eval (glDisableVertexAttribArray (0));
			//gl_eval (glDisableVertexAttribArray (1));
			gl_eval (glBindBuffer (GL_ARRAY_BUFFER, 0));
			gl_eval (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
			
			// -------------------------
			_effect = new opengl_effect ();
			
			_effect->load (
			gl_shader_source (
							  
				layout (location = 0) in vec3	in_position;
				layout (location = 1) in int	in_bone_a;
				layout (location = 2) in int	in_bone_b;
				layout (location = 3) in float	in_bone_bias;
				layout (location = 4) in vec4	in_color;
							  
				uniform vec3 in_bones_p [2];
				uniform vec4 in_bones_r [2];

				out vec4 var_color;

				void main () {
					gl_Position.xyz = in_position;
					gl_Position.w = 1.0;

					var_color = in_color;
				}
			),
			gl_shader_source (
				in vec4		var_color;
				out vec4	out_color;

				void main () {
					out_color = var_color;
				}
			)
			);

			// debug initialize
			opengl_debug::initialize ();
			
		}
		
		imesh *	opengl_device::create_mesh ()
		{
			return new opengl_mesh ();
		}
		
		itexture * opengl_device::create_texture (const point & size)
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
			//glUniformMatrix4fv (_model_location, 1, GL_FALSE, &matrix.data[0]);
			
			//glMatrixMode(GL_MODELVIEW);
			//glLoadMatrixf (&matrix.data [0]);
		}
		
		void opengl_device::set_projection ( const mat4 & matrix ) {
			//glUniformMatrix4fv (_proj_location, 1, GL_FALSE, &matrix.data [0]);
			//glMatrixMode(GL_PROJECTION);
			//glLoadTransposeMatrixf (&matrix.data [0]);
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


		void draw_joint (const joint & parent, const joint & child ) {
			opengl_debug::draw_line (parent.p, child.p, color (1., .0, .0, 1.));
			opengl_debug::draw_line (parent.p + vec3 (-.01, .0, .0), parent.p + vec3 (.01, .0, .0), color (.0, 1.0, 1.0, 1.));
			opengl_debug::draw_line (parent.p + vec3 (0, -.01, .0), parent.p + vec3 (.0, .01, .0), color (.0, 1.0, 1.0, 1.));
		}
		
		void opengl_device::end_frame ()
		{
			
			// update
			joint abones [sizeof (bones) / sizeof (joint)];
			
			quat rotation = quat::from_axis (
											 vec3 (.0, .0, 1.0),
											 angle
											 );
			
			abones [0].p = bones [0].p;
			abones [0].r = rotation;
			
			for ( int i = 1; i < sizeof (bones) / sizeof (joint); i++) {
				bones [i].r = rotation;
				abones [i] = bones [i].to_absolute(abones[i-1]);
			}
			// ------

			_effect->apply ();
			
			//if (_bone_uniform >= 0)
			//	glUniform1fv (_bone_uniform, sizeof (joint) * 2, (GLfloat *)&abones[0]);

			gl_eval(glBindVertexArray (_vertex_array_id));
			
			gl_eval(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
			
			gl_eval(glBindVertexArray (0));
			
			// ---------
			
			// draw bones
			for ( int i = 1; i < sizeof (bones) / sizeof (joint); i++) {
				draw_joint (abones [i-1], abones[i]);
			}
			
			angle += angle_inc;
			
			if (angle > .8 || angle < -.8)
				angle_inc *= -1.0;
				
			// ----------
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