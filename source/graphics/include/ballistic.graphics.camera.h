#ifndef _ballistic_graphics_camera_h_
#define _ballistic_graphics_camera_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		enum projection_type {
			projection_perspective,
			projection_ortho
		};

		class graphics_system;

		class camera : public ballistic::component {
		private:

			projection_type
				_projection_type;

			real
				_left,
				_right,
				_top,
				_bottom,
				_near,
				_far,
				_fovy;

			real 
				_depth_divisor;

			point
				_client_size;

			graphics_system *	_system;

			mat4 _proj;

			property < vec3 > * _p_target;
			property < vec3 > * _p_position;
			property < vec3 > * _p_up;

			property < mat4 > * _p_proj;
			property < mat4 > * _p_view;

			void make_ortho_projection ();
			void make_perspective_proj ();

			void update_proj ();

		public:

			static void require_properties (entity_type * new_type, component_info & info);

			static const id_t component_id;

			// constructors
			camera ();
			camera (real near, real far);

			// methods
			uint16_t depth (mat4 & transform) const;

			mat4 view () const;
			const mat4 & proj () const;

			vec3 position () const;


			// component
			virtual void notify (entity * sender, ballistic::message & message) override;

			virtual void setup (ballistic::containers::property_container & parameters) override;
			virtual void terminate () override;

		};

	}
}

#endif