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
			_game (nullptr),
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

		uint16 camera::get_depth (mat4 & transform) const {
			real z = math::length (
					vec3 (transform.m12, transform.m13, transform.m14),
					position
				);

			// 16 = bitness
			return uint16 ((1 << 16) * _depth_divisor / z);
		}

		mat4 camera::get_view () const {

			vec3 zaxis = math::normalize (target - position);
			vec3 xaxis = math::normalize (math::cross (up, zaxis));
			vec3 yaxis = math::cross (zaxis, xaxis);

			return mat4 (
				xaxis.x, yaxis.x, zaxis.x, .0,
				xaxis.y, yaxis.y, zaxis.y, .0,
				xaxis.z, yaxis.z, zaxis.z, .0,
				math::dot (xaxis, position), math::dot (yaxis, position), math::dot (zaxis, position), 1
			);
		}

		const mat4 & camera::get_proj () const {
			return _proj;
		}

		void camera::make_ortho_projection (real left, real right, real bottom, real top, real near, real far) {
			_proj =  mat4 (
				2.0 / (right - left), .0, .0, -((right + left) / (right - left)),
				.0, 2.0 / (top - bottom), .0, -((top + bottom) / (top - bottom)),
				.0, .0, -2 / (far - near), -((far + near) / (far - near)),
				.0, .0, .0, 1.
				);

			_far = far;
			_near = near;

			_depth_divisor =
				far / (far - near)
				+
				far * near / (near - far);
		}

		void camera::make_perspective_proj (real fovy, real aspect, real near, real far ) {
			real 
				ys = 1 / std::tan (fovy / 2),
				xs = ys / aspect;

			_proj =  mat4 (
				xs, .0, .0, .0,
				.0, ys, .0, .0,
				.0, .0, far / (far - near), .1,
				.0, .0, -near * far / (far - near), .0
				);

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
					debug_warn ("[ballistic::graphics::camera::notify] Graphics system not set!");
				);

				return;
			}

			if (message.get_id () == ballistic::id::message_property_changed && message.get_sender () == get_entity ()) {
				id_t property_id = message [ballistic::id::id].as < id_t > ();

				if (property_id == id::position)
					position = message [ballistic::id::value].as < vec3 > ();
				else if (property_id == id::target)
					target = message [ballistic::id::target].as < vec3 > ();
				else if (property_id == id::up)
					up = message [ballistic::id::target].as < vec3 > ();

				return;
			}

			if (message.get_id () == ballistic::id::message_initialize) {

				entity * ent = get_entity ();

				_game = ent->get_game ();
				_system = dynamic_cast <graphics_system *> (_game->find_system (ballistic::id::graphics::system));

				position = ent->get_property (ballistic::id::position).as < vec3 > ();
				target = ent->get_property (ballistic::id::target).as < vec3 > ();
				up = ent->get_property (ballistic::id::up).as < vec3 > ();
			}
		}

		void camera::setup (vector < ballistic::property > & parameters) {
			
			real
				left,
				right,
				top,
				bottom,
				near,
				far,
				fovy;


			enum {
				proj_type_ortho,
				proj_type_persp
			} type = proj_type_ortho;

			for (property & prop : parameters) {
				id_t prop_id = prop.get_id ();

				if (prop_id == id::graphics::projection) {
					if (prop.as < string > () == "ortho")
						type = proj_type_ortho;
					else if (prop.as < string > () == "proj")
						type = proj_type_persp;
					
				} else if (prop_id == id::graphics::left)
					left = (real) prop.as < double > ();
				else if (prop_id == id::graphics::right)
					right = (real)prop.as < double > ();
				else if (prop_id == id::graphics::top)
					top = (real)prop.as < double > ();
				else if (prop_id == id::graphics::bottom)
					bottom = (real)prop.as < double > ();
				else if (prop_id == id::graphics::near)
					near = (real)prop.as < double > ();
				else if (prop_id == id::graphics::far)
					far = (real)prop.as < double > ();
				else if (prop_id == id::graphics::fovy)
					fovy = (real)prop.as < double > ();

			}

			

			if (type == proj_type_ortho)
				make_ortho_projection (left, right, bottom, top, near, far);
			else if (type == proj_type_persp) 
				make_perspective_proj (fovy
		}


	}
}