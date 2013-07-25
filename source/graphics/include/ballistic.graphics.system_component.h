#ifndef _ballistic_graphics_system_component_h_
#define	_ballistic_graphics_system_component_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class system_component : public ballistic::component {
		private:

			idevice *	_device;
			camera		_camera;

		public:

			void set_device (idevice * device);
			idevice * get_device ();

			void set_camera (camera cam);
			const camera & get_camera ();

			virtual void notify ( ballistic::message & message );

			// methods
			virtual void push_item ();

		};
				  
	}
}

#endif