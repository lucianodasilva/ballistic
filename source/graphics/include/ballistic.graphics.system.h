#ifndef _ballistic_graphics_system_h
#define _ballistic_graphics_system_h

#include <ballistic.h>

#include <glm.hpp>

namespace ballistic {
	namespace graphics {
		
		class system : public ballistic::engine::icomponent {
		private:
			
			
			
		public:
			virtual void notify ( ballistic::engine::message & message );
			
		};
		
	}
}

#endif
