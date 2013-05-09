#ifndef _ballistic_graphics_visual_component_h_
#define _ballistic_graphics_visual_component_h_

#include <Ballistic.h>

namespace ballistic {
	namespace graphics {
		
		class visual_component : public icomponent {
		public:

			virtual void setup ();
			
			virtual void notify ( ballistic::message & message );
			
		};
		
	}
}

#endif
