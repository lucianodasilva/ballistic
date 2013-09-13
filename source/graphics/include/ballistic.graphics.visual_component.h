#ifndef _ballistic_graphics_visual_component_h_
#define	_ballistic_graphics_visual_component_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class visual_component : public ballistic::component {
		private:

			mat4				_transform;

			imaterial *			_material;
			imesh *				_mesh;

			graphics_system *	_system;
			game *				_game;

		public:

			static const id_t component_id;

			visual_component ();

			virtual void notify ( ballistic::message & message );

			virtual void setup (vector < ballistic::property > & parameters);

		};
				  
	}
}

#endif