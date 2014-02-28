#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

namespace ballistic {
	namespace graphics {

		const id_t camera::component_id = id::graphics::camera;

		camera::camera () {}

		camera::camera (const camera & v)
			: 
			_near (v._near), 
			_far (v._far), 
			_depth_divisor (v._depth_divisor),
			target (v.target),
			position (v.position),
			up (v.up)
		{}

		camera::camera (real near, real far) 
			: 
			_near (near),
			_far (far),
			_system (nullptr)
		{
			_depth_divisor =
				far / (far - near)
				+
				far * near / (near - far);
		}

		const camera & camera::operator= (const camera & v) {
			_near = v._near;
			_far = v._far;
			_depth_divisor = v._depth_divisor;
			target = v.target;
			position = v.position;
			up = v.up;
			return *this;
		}

		uint16_t camera::depth (mat4 & transform) const {
			real z = math::length (
					vec3 {transform.m12, transform.m13, transform.m14},
					position
				);

			// 16 = bitness
			return uint16_t ((1 << 16) * _depth_divisor / z);
		}

		mat4 camera::view () const {

			vec3 zaxis = normalize (target - position);
			vec3 yaxis = normalize (up);
			vec3 xaxis = normalize (cross (zaxis, yaxis));
			yaxis = cross (xaxis, zaxis);

			return {
				xaxis.x, yaxis.x, -zaxis.x, .0,
				xaxis.y, yaxis.y, -zaxis.y, .0,
				xaxis.z, yaxis.z, -zaxis.z, .0,
				-dot (xaxis, position), -dot (yaxis, position), dot (zaxis, position), 1.
			};
		}

		const mat4 & camera::proj () const {
			return _proj;
		}

		void camera::make_ortho_projection (real left, real right, real bottom, real top, real near, real far) {

			_proj = {
				real (2) / (right - left), real (0), real (0), real (0),
				real (0), real (2) / (top - bottom), real (0), real (0),
				real (0), real (0), real (1) / (far - near), real (0),
				real (0), real (0), near / (near - far), real (1)
			};

			_far = far;
			_near = near;

			_depth_divisor =
				far / (far - near)
				+
				far * near / (near - far);

		}

		void camera::make_perspective_proj (real fov, real aspect, real near, real far ) {

			real
				fov_r = math::radians (fov),
				range = tan (fov_r / real (2)) * near,
				l = -range * aspect,
				r = range * aspect,
				b = -range,
				t = range;


			_proj = {
				(real (2) * near) / (r - l), .0, .0, .0,
				.0, (real (2) * near) / (t - b), .0, .0,
				.0, .0, -(far + near) / (far - near), real (-1),
				.0, .0, -(real (2) * far * near) / (far - near), .0
			};
			
			_far = far;
			_near = near;

			_depth_divisor =
				far / (far - near)
				+
				far * near / (near - far);

		}

		void camera::notify (entity * sender, ballistic::message & message) {

			if (message.id () == ballistic::id::message_update) {
				if (_system)
					_system->camera (this);
				debug_run (else
					debug_print ("graphics system not set!");
				);
			} else if (message.id () == ballistic::id::message_property_changed) {
				id_t property_id = message [ballistic::id::id];

				if (property_id == id::position) {
					position = message [ballistic::id::value];
				} else if (property_id == id::target) {
					target = message [ballistic::id::target];
				} else if (property_id == id::up) {
					up = message [ballistic::id::up];
				}
			} else {
				// initialize
				_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

				position =	sender->properties [ballistic::id::position];
				target =	sender->properties [ballistic::id::target];
				up =		sender->properties [ballistic::id::up];
			}

		}

		void camera::setup (entity * parent, property_container & parameters) {
			component::setup (parent, parameters);

			// bind to local message notifier
			container ()->local_notifier.attach (id::message_property_changed, this);
			// bind to global message notifier
			game::instance.global_notifier.attach (id::message_update, this);
			
			real
				left = 0,
				right = 0,
				top = 0,
				bottom = 0,
				near = 0,
				far = 0,
				fovy = 0;
			
			
			enum {
				proj_type_ortho,
				proj_type_persp
			} type = proj_type_ortho;

			string proj_type_value = parameters [id::graphics::projection];
			
			if (proj_type_value == "ortho")
				type = proj_type_ortho;
			else if (proj_type_value == "perspective")
				type = proj_type_persp;
			else {
				debug_print ("unknown projection type \"" << proj_type_value << "\". default to ortho.");
			}
			
			left = parameters [id::graphics::left];
			right = parameters [id::graphics::right];
			top = parameters [id::graphics::top];
			bottom = parameters[id::graphics::bottom];
			near = parameters[id::graphics::near];
			far = parameters [id::graphics::far];
			fovy = parameters [id::graphics::fov];
			
			
			if (type == proj_type_ortho)
				make_ortho_projection (left, right, bottom, top, near, far);
			else if (type == proj_type_persp) {
				point size = game::instance.frontend ()->get_client_size ();
				make_perspective_proj (fovy, real (size.x) / real (size.y), near, far);
			}
		}

		void camera::terminate () {
			// bind to local message notifier
			container ()->local_notifier.detach (id::message_property_changed, this);
			// bind to global message notifier
			game::instance.global_notifier.detach (id::message_update, this);
		}

	}
}