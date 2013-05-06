#ifndef _ballistic_graphics_visual_component_h_
#define _ballistic_graphics_visual_component_h_

#include <Ballistic.h>

namespace ballistic {
	namespace graphics {
		
		class visual_component : public engine::icomponent {
		private:
		public:
			
			virtual void notify ( ballistic::engine::message & message );
			
		};
		
	}
}

#endif
