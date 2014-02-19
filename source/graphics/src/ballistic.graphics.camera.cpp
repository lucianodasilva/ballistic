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

		uint16_t camera::get_depth (mat4 & transform) const {
			real z = math::length (
					vec3 {transform.m12, transform.m13, transform.m14},
					position
				);

			// 16 = bitness
			return uint16_t ((1 << 16) * _depth_divisor / z);
		}

		mat4 camera::get_view () const {

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

		const mat4 & camera::get_proj () const {
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

		void camera::notify (ballistic::message & message) {

			if (message.get_id () == ballistic::id::message_update)  {
				if (_system)
					_system->set_camera (this);
				debug_run (else
					debug_print ("[ballistic::graphics::camera::notify] Graphics system not set!");
				);

				return;
			}

			if (message.get_id () == ballistic::id::message_property_changed && message.get_sender () == get_entity ()) {
				id_t property_id = message [ballistic::id::id];

				if (property_id == id::position)
					position = message [ballistic::id::value];
				else if (property_id == id::target)
					target = message [ballistic::id::target];
				else if (property_id == id::up)
					up = message [ballistic::id::target];

				return;
			}

			if (message.get_id () == ballistic::id::message_initialize) {

				entity * ent = get_entity ();

				_system = dynamic_cast <graphics_system *> (get_game ()->find_system (ballistic::id::graphics::system));

				position = ent->properties [ballistic::id::position];
				target = ent->properties [ballistic::id::target];
				up = ent->properties [ballistic::id::up];
			}
		}

		void camera::setup (entity * parent, property_map & parameters) {
			component::setup (parent, parameters);
			
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

			for (auto & prop_pair : parameters) {
				id_t prop_id = prop_pair.first;
				var & prop = prop_pair.second;

				if (prop_id == id::graphics::projection) {
					if ((text)prop == "ortho")
						type = proj_type_ortho;
					else if ((text)prop == "perspective")
						type = proj_type_persp;
					
				} else if (prop_id == id::graphics::left)
					left = prop;
				else if (prop_id == id::graphics::right)
					right = prop;
				else if (prop_id == id::graphics::top)
					top = prop;
				else if (prop_id == id::graphics::bottom)
					bottom = prop;
				else if (prop_id == id::graphics::near)
					near = prop;
				else if (prop_id == id::graphics::far)
					far = prop;
				else if (prop_id == id::graphics::fov)
					fovy = prop;

			}

			

			if (type == proj_type_ortho)
				make_ortho_projection (left, right, bottom, top, near, far);
			else if (type == proj_type_persp) {
				point size = get_game ()->get_frontend ()->get_client_size ();
				make_perspective_proj (fovy, real (size.x) / real (size.y), near, far);
			}
		}


	}
}