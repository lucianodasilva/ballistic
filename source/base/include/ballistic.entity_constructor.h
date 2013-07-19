#ifndef	_ballistic_entity_constructor_h_
#define _ballistic_entity_constructor_h_

#include <functional>
#include <vector>
#include <string>


#include "ballistic.component_constructor.h"
#include "ballistic.resources.iresource.h"
#include "ballistic.attribute.h"
#include "ballistic.id.h"
#include "ballistic.var.h"

#include <string>
#include <vector>

using namespace std;

namespace ballistic {
	
	class entity;
	
	class entity_constructor : public resources::iresource {
	private:
		
		vector < attribute > _attributes;
		vector < icomponent_constructor * > _components;
		
	public:

		vector < attribute > & get_attributes ();
		vector < icomponent_constructor * > & get_components ();

		entity * create ();

	};

}


#endif