#ifndef _ballistic_graphics_overlay_h_
#define	_ballistic_graphics_overlay_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.visual.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class overlay : public ballistic::graphics::visual {
		public:

			static const id_t component_id;

			overlay ();

			virtual void notify ( entity * sender, ballistic::message & message ) override;

		};
				  
	}
}

#endif