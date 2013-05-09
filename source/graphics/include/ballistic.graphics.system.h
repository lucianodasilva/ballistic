#ifndef _ballistic_graphics_system_h
#define _ballistic_graphics_system_h

#include <ballistic.h>
#include <glm.hpp>
#include <vector>

#include "ballistic.graphics.irenderable.h"
#include "ballistic.graphics.render_item.h"

using namespace std;
using namespace glm;

namespace ballistic {
	namespace graphics {

		class system : public ballistic::icomponent {
		private:
			
			ballistic::message			_message_inst;
			vector < render_item >	_render_items;
			
		public:

			virtual void set_entity ( entity * ent );

			system ();

			void add_render_item ( irenderable * renderable, const mat4 & transform, graphics::material * mat );

			virtual void notify ( ballistic::message & message );
			
		};
		
	}
}

#endif
