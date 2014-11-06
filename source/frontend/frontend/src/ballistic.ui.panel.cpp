#include "ballistic.ui.panel.h"

namespace ballistic {
	namespace ui {

		void panel::on_draw (const draw & d) {
			d.draw_rect (
				this->background_color,
				to_absolute ((vec2)this->location),
				to_absolute ((vec2)this->location + (vec2)this->size)
			);

			control::on_draw (d);
		}


	}
}