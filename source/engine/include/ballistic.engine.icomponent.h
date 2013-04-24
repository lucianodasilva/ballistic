
#ifndef _ballistic_engine_icomponent_h_
#define _ballistic_engine_icomponent_h_

namespace ballistic {
	namespace engine {
	
		class icomponent {
		public:
			
			virtual void on_message () = 0;
			
		};
		
	}
}

#endif
