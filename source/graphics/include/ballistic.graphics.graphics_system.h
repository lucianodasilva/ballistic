#ifndef _ballistic_graphics_graphics_system_h_
#define	_ballistic_graphics_graphics_system_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.render_list.h"

namespace ballistic {
	namespace graphics {

		class graphics_system : public ballistic::isystem {
		private:

			idevice *	_device;
			camera		_camera;

			message		_render_message;

			render_list _render_list;

		public:

			graphics_system ();

			virtual id_t get_id ();

			void set_device (idevice * device);
			idevice * get_device ();

			void set_camera (camera cam);
			const camera & get_camera ();

			void render ();

			virtual void notify ( ballistic::message & message );

			// methods
			virtual void push_item ( imaterial * material, imesh * mesh, const mat4 & transform );

		};
				  
	}
}

#endif