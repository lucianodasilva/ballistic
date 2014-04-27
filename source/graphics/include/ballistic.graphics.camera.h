#ifndef _ballistic_graphics_camera_h_
#define _ballistic_graphics_camera_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class camera : public ballistic::component {
		private:

			real _near;
			real _far;

			real _depth_divisor;

			graphics_system *	_system;

			mat4 _proj;

			property < vec3 > * _p_target;
			property < vec3 > * _p_position;
			property < vec3 > * _p_up;

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

			// utilities
			void make_ortho_projection (real left, real right, real bottom, real top, real near, real far);
			void make_perspective_proj (real fov, real aspect, real near, real far );

			// component
			virtual void notify (entity * sender, ballistic::message & message) override;

			virtual void setup (entity * parent, containers::property_container & parameters) override;
			virtual void terminate () override;

		};

	}
}

#endif