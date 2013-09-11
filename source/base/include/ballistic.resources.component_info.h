#ifndef _ballistic_resources_component_info_h_
#define _ballistic_resources_component_info_h_

#include <type_traits>
#include <vector>

#include "ballistic.property.h"

using namespace std;

namespace ballistic {
	
	class icomponent;
	
	namespace resources {
		
		class icomponent_constructor;
		
		class component_info : public iproperty_container {
		private:
			
			vector < property > _properties;
			icomponent_constructor * _constructor;
			
		public:

			component_info ();
			
			icomponent_constructor * get_constructor ();
			void set_constructor ( icomponent_constructor * ctor );
			
			// property container
			virtual property & add_property (id_t id, const var & v);

			virtual bool has_property (id_t id);

			virtual property & get_property (id_t id);
			// -------------------
			
			icomponent * create ();
			
		};
		
	}

}

#endif