#ifndef _ballistic_resources_component_info_h_
#define _ballistic_resources_component_info_h_

#include <type_traits>
#include <vector>

#include "ballistic.attribute.h"

using namespace std;

namespace ballistic {
	
	class icomponent;
	
	namespace resources {
		
		class icomponent_constructor;
		
		class component_info {
		private:
			
			vector < attribute > _attributes;
			icomponent_constructor * _constructor;
			
		public:
			
			icomponent_constructor * get_constructor ();
			void set_constructor ( icomponent_constructor * ctor );
			
			vector < attribute > & get_attributes ();
			
			icomponent * create ();
			
		};
		
	}

}

#endif