#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

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
			_far (far)
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

		uint16 camera::get_depth (mat4 & transform) {
			real z = math::length (
					vec3 (transform.m12, transform.m13, transform.m14),
					position
				);

			return uint16 ((1 << 16) * _depth_divisor / z);
		}

		mat4 camera::get_view () {

			vec3 zaxis = math::normalize (target - position);
			vec3 xaxis = math::normalize (math::cross (up, zaxis));
			vec3 yaxis = math::cross (zaxis, xaxis);

			return mat4 (
				xaxis.x, yaxis.x, zaxis.x, .0,
				xaxis.y, yaxis.y, zaxis.y, .0,
				xaxis.z, yaxis.z, zaxis.z, .0,
				-math::dot (xaxis, position), -math::dot (yaxis, position), -math::dot (zaxis, position), 1
			);
		}

	}
}