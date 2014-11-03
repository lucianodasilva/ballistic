#ifndef _ballistic_ui_renderer_h_
#define _ballistic_ui_renderer_h_

#include <ballistic.graphics.h>
#include <ballistic.ui.draw.h>

namespace ballistic {
	namespace ui {

		class component;
		class control;

		class renderer : public ballistic::graphics::irenderable {
		private:

			control *	_root;
			draw		_draw_instance;

		public:

			renderer ();

			control * root () const;
			control * root (control * r);

			virtual uint8_t run_id () const;

			virtual void apply (graphics::idevice * device);
			virtual void render ();

			virtual aabox bounding_box () const;


		};

	}
}

#endif