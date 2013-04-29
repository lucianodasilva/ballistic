
#ifndef _ballistic_engine_icomponent_h_
#define _ballistic_engine_icomponent_h_

#include "ballistic.engine.message.h"

namespace ballistic {
	namespace engine {
	
		class icomponent {
		public:

			virtual inline ~icomponent () {}
			
			virtual void notify ( ballistic::engine::message & message ) = 0;
			
		};

		template < void (*message_handle)( ballistic::engine::message & ) >
		class func_component : public icomponent {
		public:

			virtual inline void notify ( ballistic::engine::message & message );

		};

		template < void (*message_handle)( ballistic::engine::message & ) >
		void func_component < message_handle >::notify ( ballistic::engine::message & message ) {
			message_handle (message);
		}

	}
}

#endif
