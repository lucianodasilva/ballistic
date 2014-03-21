#ifndef _ballistic_graphics_visual_h_
#define	_ballistic_graphics_visual_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class visual : public ballistic::component {
		private:

			property < vec3 > *			_position;
			property < vec3 > *			_rotation;
			property < vec3 > *			_scale;

			property < imaterial * > *	_material;
			property < imesh * > *		_mesh;

			graphics_system *			_system;

		public:

			static const id_t component_id;

			visual ();

			virtual void notify ( entity * sender, ballistic::message & message ) override;

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (entity * parent, property_container & parameters) override;

			virtual void terminate ();
		};
				  
	}
}

#endif