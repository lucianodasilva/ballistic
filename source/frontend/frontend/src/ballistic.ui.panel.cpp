#include "ballistic.ui.panel.h"

namespace ballistic {
	namespace ui {

		void panel::on_draw (const draw & d) {
			d.draw_rect (
				this->background_color (),
				to_absolute (this->location ()),
				to_absolute (this->location () + this->size ())
			);

			control::on_draw (d);
		}


	}
}