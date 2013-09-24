#ifndef _ballistic_graphics_visual_h_
#define	_ballistic_graphics_visual_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.camera.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class visual : public ballistic::component {
		private:

			mat4				_transform;

			imaterial *			_material;
			imesh *				_mesh;

			graphics_system *	_system;
			igame *				_game;

		public:

			static const id_t component_id;

			visual ();

			virtual void notify ( ballistic::message & message );

			virtual void setup (vector < ballistic::property > & parameters);

		};
				  
	}
}

#endif