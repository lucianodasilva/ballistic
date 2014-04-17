#ifndef _ballistic_graphics_font_rendering_system_h_
#define	_ballistic_graphics_font_rendering_system_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.iraster_font.h"

#include <string>

namespace ballistic {
	namespace graphics {

		class graphics_system;
		class imesh;

		class font_rendering_system : public ballistic::isystem {
		private:

			graphics_system *	_graphics;
			imesh *				_mesh;

		public:

			font_rendering_system ();

			virtual id_t id ();

			virtual void notify ( entity * sender, ballistic::message & message );

			virtual void attach ();
			virtual void detach ();

			// methods
			void render_string (const string & text, real x, real y, uint8_t layer, iraster_font * font, color color);

		};
				  
	}
}

#endif