#include "ballistic.graphics.font_rendering_system.h"
#include "ballistic.graphics.common_id.h"

namespace ballistic {
	namespace graphics {

		id_t font_rendering_system::id () {
			return ballistic::id::graphics::font_renderer;
		}

		font_rendering_system::font_rendering_system () {}

		void font_rendering_system::notify (entity * sender, ballistic::message & message) {}

		void font_rendering_system::attach () {}

		void font_rendering_system::detach () {}

	}
}