#ifndef _ballistic_graphics_visual_h_
#define	_ballistic_graphics_visual_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

#include "ballistic.graphics.rig.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class material;

		class visual : public ballistic::component {
		protected:

			property < mat4 > *			_transform;

			property < material * > *	_material;

			property < rig_frame_tween * > * _rig_tween;

			property < imesh * > *		_mesh;

			property < uint8_t > *		_layer;

			graphics_system *			_system;

		public:

			static const id_t component_id;

			visual ();

			virtual void notify ( entity * sender, ballistic::message & message ) override;

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::containers::property_container & parameters) override;

			virtual void terminate ();
		};
				  
	}
}

#endif