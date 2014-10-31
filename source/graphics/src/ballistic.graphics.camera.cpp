#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

namespace ballistic {
	namespace graphics {

		void camera::require_properties (entity_type * new_type, component_info & info) {
			// entity requirements
			new_type->properties
				.require (id::position, vec3 ({.0, .0, .0}))
				.require (id::target, vec3 ({.0, .0, .0}))
				.require (id::up, vec3 ({.0, 1.0, .0}))
				.require < mat4 > (id::graphics::camera_proj)
				.require < mat4 > (id::graphics::camera_view);

			// component arguments
			info.properties
				.require < string > (id::graphics::projection, "ortho")
				.require < real > (id::graphics::near, .0)
				.require < real > (id::graphics::far, .0)
				.require < real > (id::graphics::left, .0)
				.require < real > (id::graphics::right, .0)
				.require < real > (id::graphics::top, .0)
				.require < real > (id::graphics::bottom, .0)
				.require < real > (id::graphics::fov, .0);
		}

		const id_t camera::component_id = id::graphics::camera;

		camera::camera () : 
			_system (nullptr)
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

		uint16_t camera::depth (mat4 & transform) const {
			real z = math::length (
					vec3 {transform.m12, transform.m13, transform.m14},
					(vec3)*_p_position
				);

			// 16 = bitness
			return uint16_t ((1 << 16) * _depth_divisor / z);
		}

		mat4 camera::view () const {

			using namespace ballistic::math;

			vec3
				target = *_p_target,
				position = *_p_position,
				up = *_p_up;

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

		vec3 camera::position () const {
			return *_p_position;
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

			if (_system)
				_system->camera (this);
			debug_run (else
				debug_print ("graphics system not set!");
			);

			*_p_view = view ();

		}

		void camera::setup (containers::property_container & parameters) {
			component::setup (parameters);

			// bind to global message notifier
			game ().global_notifier.attach (id::message::update, this);

			// get graphics system in use
			_system = dynamic_cast <graphics_system *> (game ().systems [id::graphics::system]);
			
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

			string projection_type = parameters [id::graphics::projection].as < string > ();

			if (projection_type == "ortho")
				type = proj_type_ortho;
			else if (projection_type == "perspective")
				type = proj_type_persp;
			else {
				debug_print ("unknown projection type \"" << projection_type << "\". default to ortho.");
			}
			
			left	= parameters [id::graphics::left];
			right	= parameters [id::graphics::right];
			top		= parameters [id::graphics::top];
			bottom	= parameters [id::graphics::bottom];
			near	= parameters [id::graphics::near];
			far		= parameters [id::graphics::far];
			fovy	= parameters [id::graphics::fov];
			
			
			if (type == proj_type_ortho)
				make_ortho_projection (left, right, bottom, top, near, far);
			else if (type == proj_type_persp) {
				//point size = parent->game ().frontend ()->get_client_size ();
				//make_perspective_proj (fovy, real (size.x) / real (size.y), near, far);
			}

			auto & properties = parent ().properties;

			_p_position = properties.aquire < vec3 > (id::position);
			_p_target = properties.aquire < vec3 > (id::target);
			_p_up = properties.aquire < vec3 > (id::up);

			_p_view = properties.aquire < mat4 > (id::graphics::camera_view);
			_p_proj = properties.aquire < mat4 > (id::graphics::camera_proj);
			*_p_proj = _proj;
		}

		void camera::terminate () {
			// unbind to global message notifier
			game ().global_notifier.detach (id::message::update, this);
		}

	}
}