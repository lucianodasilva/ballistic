#ifndef _ballistic_ui_panel_h_
#define _ballistic_ui_panel_h_

#include <ballistic.graphics.h>
#include "ballistic.ui.control.h"

namespace ballistic {
	namespace ui {

		class panel : public ui::control {
		protected:

			virtual void on_draw (const draw & d);

		public:


		};

	}
}

#endif