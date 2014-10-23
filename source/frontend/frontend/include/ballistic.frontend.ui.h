#ifndef _ballistic_frontend_ui_h_
#define _ballistic_frontend_ui_h_

#include <ballistic.graphics.h>
#include "ballistic.frontend.ui_control.h"

namespace ballistic {
	namespace frontend {

		class ui : public graphics::overlay, public control {
		public:

			static const id_t component_id;

			ui ();

			virtual void setup (entity * parent, ballistic::containers::property_container & parameters) override;

			virtual void terminate () override;

			virtual void notify (entity * sender, ballistic::message & message) override;

		};

	}
}

#endif