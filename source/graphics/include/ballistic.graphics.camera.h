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

		public:

			static const id_t component_id;

			vec3 target;
			vec3 position;
			vec3 up;

			// constructors
			camera ();
			camera (const camera & v);
			camera (real near, real far);

			// attribution
			const camera & operator = (const camera &v);

			// methods
			uint16_t get_depth (mat4 & transform) const;

			mat4 get_view () const;
			const mat4 & get_proj () const;

			// utilities
			void make_ortho_projection (real left, real right, real bottom, real top, real near, real far);
			void make_perspective_proj (real fov, real aspect, real near, real far );

			// component
			virtual void notify (ballistic::message & message) override;

			virtual void setup (entity * parent, property_container & parameters) override;

		};

	}
}

#endif