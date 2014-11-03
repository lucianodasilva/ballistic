#include "ballistic.ui.renderer.h"
#include "ballistic.ui.common.h"
#include "ballistic.ui.component.h"

namespace ballistic {
	namespace ui {

		renderer::renderer () : irenderable (id::null), _root (nullptr) {}

		control * renderer::root () const {
			return _root;
		}

		control * renderer::root (control * r) {
			_root = r;
			return r;
		}

		uint8_t renderer::run_id () const{
			return 0;
		}

		void renderer::apply (graphics::idevice * device) {
			_draw_instance.device (device);
		}

		void renderer::render () {
			if (_root)
				_root->on_draw (_draw_instance);
			debug_run (
			else
				debug_print ("undefined root control. cannot render controls.");
			)
		}

		aabox renderer::bounding_box () const {
			return aabox ();
		}

	}
}