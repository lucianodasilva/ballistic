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

		const auto message_render_frame	= hash < string > ()("message_render_frame");
		const auto message_render_frame_system = hash < string > ()("message_render_frame_system");

		class system : public ballistic::engine::icomponent {
		private:
			
			engine::message			_message_inst;
			vector < render_item >	_render_items;
			
		public:

			virtual void set_entity ( engine::entity * ent );

			system ();

			void add_render_item ( irenderable * renderable, const mat4 & transform );

			virtual void notify ( ballistic::engine::message & message );
			
		};
		
	}
}

#endif
