#ifndef _ballistic_graphics_font_rendering_system_h_
#define	_ballistic_graphics_font_rendering_system_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.iraster_font.h"

#include <string>

namespace ballistic {
	namespace graphics {

		class font_rendering_system : public ballistic::isystem {
		public:

			font_rendering_system ();

			virtual id_t id ();

			virtual void notify ( entity * sender, ballistic::message & message );

			virtual void attach ();
			virtual void detach ();

			// methods
			void render_string (const string & text, real x, real y, real size, iraster_font * font, color color);

		};
				  
	}
}

#endif