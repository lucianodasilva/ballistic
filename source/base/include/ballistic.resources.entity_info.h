#ifndef	_ballistic_resources_entity_info_h_
#define _ballistic_resources_entity_info_h_

#include <functional>
#include <vector>
#include <string>

#include "ballistic.resources.component_info.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.property.h"
#include "ballistic.id.h"

#include <string>
#include <vector>

using namespace std;

namespace ballistic {
	
	class entity;
	class igame;
	
	namespace resources {
		
		class entity_info : public resources::iresource, public iproperty_container {
		private:
			
			vector < property > _properties;
			vector < component_info > _components;
			
		public:

			vector < property > & get_properties ();
			vector < component_info > & get_components ();

			// property container
			virtual property & add_property (id_t id, const var & v);

			virtual bool has_property (id_t id);

			virtual property & get_property (id_t id);
			// -------------------

			entity * create (igame * game, id_t id);

		};
		
	}

}


#endif