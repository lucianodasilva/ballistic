#ifndef _ballistic_frontend_ui_control_h_
#define _ballistic_frontend_ui_control_h_

#include <functional>

#include <ballistic.graphics.h>
#include "ballistic.frontend.draw.h"

namespace ballistic {
	namespace frontend {

		class ui : public graphics::overlay {
		private:

			

		public:



			rect bounds;

			

			virtual void on_paint (const draw & d);

		};

	}
}

#endif