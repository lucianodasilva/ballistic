#ifndef _ballistic_resources_component_info_h_
#define _ballistic_resources_component_info_h_

#include <type_traits>
#include <vector>

#include "ballistic.property_container.h"

using namespace std;

namespace ballistic {
	
	class icomponent;
	class entity;
	
	namespace resources {
		
		class icomponent_constructor;
		
		class component_info {
		private:

			icomponent_constructor * _constructor;
			
		public:

			component_info ();
			
			icomponent_constructor * get_constructor ();
			void set_constructor ( icomponent_constructor * ctor );
			
			property_container properties;
			
			icomponent * create (entity * parent);
			
		};
		
	}

}

#endif