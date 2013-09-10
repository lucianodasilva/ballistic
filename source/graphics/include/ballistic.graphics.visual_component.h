#ifndef _ballistic_graphics_visual_component_h_
#define	_ballistic_graphics_visual_component_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class system_component;

		class visual_component : public ballistic::component {
		private:

			mat4				_transform;

			imaterial *			_material;
			imesh *				_mesh;

			system_component *	_system;

		public:

			visual_component ();

			virtual void notify ( ballistic::message & message );

			virtual void setup (vector < ballistic::property > & parameters);

		};
				  
	}
}

#endif