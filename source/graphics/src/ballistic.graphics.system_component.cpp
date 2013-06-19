#include "ballistic.graphics.system_component.h"

namespace ballistic {
	namespace graphics {

		void system_component::notify ( ballistic::message & message ) {

			if (message.get_id () != ballistic::id::message_update) return;

			_device->begin_frame ();


			_device->end_frame ();
			_device->present ();
		}

	}
}