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
				.require < mat4 > (id::camera::proj)
				.require < mat4 > (id::camera::view);

			// component arguments
			info.properties
				.require < string > (id::camera::projection, "ortho")
				.require < real >	(id::camera::near, .0)
				.require < real >	(id::camera::far, .0)
				.require < real >	(id::camera::left, .0)
				.require < real >	(id::camera::right, .0)
				.require < real >	(id::camera::top, .0)
				.require < real >	(id::camera::bottom, .0)
				.require < real >	(id::camera::fov, .0);
		}

		const id_t camera::component_id = id::camera::id;

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

		void camera::make_ortho_projection () {

			_proj = {
				real (2) / (_right - _left), real (0), real (0), real (0),
				real (0), real (2) / (_top - _bottom), real (0), real (0),
				real (0), real (0), real (1) / (_far - _near), real (0),
				real (0), real (0), _near / (_near - _far), real (1)
			};

			_depth_divisor =
				_far / (_far - _near)
				+
				_far * _near / (_near - _far);

		}

		void camera::make_perspective_proj () {

			real aspect = real (_client_size.x) / real (_client_size.y);

			real
				fov_r = math::radians (_fovy),
				range = tan (fov_r / real (2)) * _near,
				l = -range * aspect,
				r = range * aspect,
				b = -range,
				t = range;

			_proj = {
				(real (2) * _near) / (r - l), .0, .0, .0,
				.0, (real (2) * _near) / (t - b), .0, .0,
				.0, .0, -(_far + _near) / (_far - _near), real (-1),
				.0, .0, -(real (2) * _far * _near) / (_far - _near), .0
			};

			_depth_divisor =
				_far / (_far - _near)
				+
				_far * _near / (_near - _far);

		}

		void camera::update_proj () {

			if (_projection_type == projection_ortho)
				make_ortho_projection ();
			else if (_projection_type == projection_perspective) {
				_client_size = game ().properties [id::frontend::client_size];
				make_perspective_proj ();
			}
		}

		void camera::notify (entity * sender, ballistic::message & message) {

			id_t message_id = message.id ();

			if (message_id == id::message::update) {
				if (_system)
					_system->camera (this);
				debug_run (else
						   debug_print ("graphics system not set!");
				);

				*_p_view = view ();
			} else if (message_id == id::message::client_size_changed) {
				update_proj ();
			}

		}

		void camera::setup (containers::property_container & parameters) {
			component::setup (parameters);

			// bind to global message notifier
			game ().global_notifier.attach ({id::message::update, id::message::client_size_changed}, this);

			// get graphics system in use
			_system = dynamic_cast <graphics_system *> (game ().systems [id::graphics::system]);
			
			string str_proj = parameters [id::camera::projection].as < string > ();

			if (str_proj == "ortho")
				_projection_type = projection_ortho;
			else if (str_proj == "perspective")
				_projection_type = projection_perspective;
			else {
				debug_print ("unknown projection type \"" << str_proj << "\". default to ortho.");
			}
			
			_left	= parameters [id::camera::left];
			_right	= parameters [id::camera::right];
			_top	= parameters [id::camera::top];
			_bottom	= parameters [id::camera::bottom];
			_near	= parameters [id::camera::near];
			_far	= parameters [id::camera::far];
			_fovy	= parameters [id::camera::fov];
			
			update_proj ();

			auto & properties = parent ().properties;

			_p_position = properties.aquire < vec3 > (id::position);
			_p_target = properties.aquire < vec3 > (id::target);
			_p_up = properties.aquire < vec3 > (id::up);

			_p_view = properties.aquire < mat4 > (id::camera::view);
			_p_proj = properties.aquire < mat4 > (id::camera::proj);
			*_p_proj = _proj;
		}

		void camera::terminate () {
			// unbind to global message notifier
			game ().global_notifier.detach ({id::message::update, id::message::client_size_changed}, this);
		}

	}
}