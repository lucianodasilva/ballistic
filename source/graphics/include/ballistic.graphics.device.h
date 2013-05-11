#ifndef _ballistic_graphics_device_h
#define _ballistic_graphics_device_h

#include <ballistic.h>
#include <glm.hpp>
#include <vector>

#include "ballistic.graphics.irenderable.h"
#include "ballistic.graphics.render_item.h"

using namespace std;
using namespace glm;

namespace ballistic {
	namespace graphics {

		class device : public ballistic::icomponent {
		private:
			
			ballistic::message			_message_inst;
			vector < render_item >	_render_items;
			
			mat4 _projection;
			mat4 _view;
			
		public:

			virtual void set_entity ( entity * ent );

			device ();

			void add_render_item ( irenderable * renderable, const mat4 & transform, graphics::material * mat );
			
			mat4 & projection_matrix ();
			mat4 & view_matrix ();

			virtual void setup ();
			virtual void notify ( ballistic::message & message );
			
		};
		
	}
}

#endif
