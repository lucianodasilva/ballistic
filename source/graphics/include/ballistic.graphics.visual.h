#ifndef _ballistic_graphics_visual_h_
#define _ballistic_graphics_visual_h_

#include <Ballistic.h>

namespace ballistic {
	namespace graphics {
		
		class visual : public icomponent {
		public:

			virtual void setup ();
			
			virtual void notify ( ballistic::message & message );
			
		};
		
	}
}

#endif
