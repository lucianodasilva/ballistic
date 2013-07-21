#ifndef	_ballistic_resources_entity_info_h_
#define _ballistic_resources_entity_info_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.resources.component_info.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.attribute.h"
#include "ballistic.id.h"

#include <string>
#include <vector>

using namespace std;

namespace ballistic {
	
	class entity;
	
	namespace resources {
		
		class entity_info : public resources::iresource {
		private:
			
			vector < attribute > _attributes;
			vector < component_info > _components;
			
		public:

			vector < attribute > & get_attributes ();
			vector < component_info > & get_components ();

			entity * create (id_t id);

		};
		
	}

}


#endif