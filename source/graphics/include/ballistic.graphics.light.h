#ifndef	_ballistic_graphics_light_h_
#define _ballistic_graphics_light_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class graphics_system;

		struct light_info {
			union {
				real data [8];
				vec3 position;
				struct {
					vec4 _h1;
					vec3 color;
					real intensity;
				};
				struct {
					vec3 _h2;
					real fallout;
				};
			};
		};

		class light : public ballistic::component {
		private:

			graphics_system * _system;
			property < vec3 > * _p_position;
			property < color > * _p_color;
			property < real > * _p_intensity;
			property < real > * _p_fallout;

		public:

			static const id_t component_id;

			light ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::containers::property_container & parameters);

			virtual void terminate ();
			virtual void notify (ballistic::entity * sender, ballistic::message & message);

		};

	}
}

#endif