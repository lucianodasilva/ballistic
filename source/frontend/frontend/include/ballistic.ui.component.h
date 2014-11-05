#ifndef _ballistic_ui_component_h_
#define _ballistic_ui_component_h_

#include <ballistic.graphics.h>

#include "ballistic.ui.control.h"
#include "ballistic.ui.renderer.h"

namespace ballistic {
	namespace ui {

		class component : public ballistic::component {
		private:
			
			draw						_draw;
			renderer					_renderer;
			graphics::material			_material;
			graphics::graphics_system *	_system;
			property < uint8_t > *		_layer;
			property < control * > *	_control;

		public:

			uint8_t layer () const;
			uint8_t layer (uint8_t v);

			static const id_t component_id;

			component ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::containers::property_container & parameters) override;

			virtual void terminate () override;

			virtual void notify (entity * sender, ballistic::message & message) override;

		};

	}
}

#endif