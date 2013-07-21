#ifndef _ballistic_debug_h_
#define _ballistic_debug_h_

#ifdef BALLISTIC_DEBUG

namespace ballistic {
	
	class debug_service {
	public:
		
		class idebug_frontend {
		public:
			
			
			
		};
		
	};
	
}


#else
#	define debug_warn(x)
#	define debug_error(x)
#endif

#endif