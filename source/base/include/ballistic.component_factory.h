#ifndef	_ballistic_component_factory_h_
#define _ballistic_component_factory_h_

#include <functional>
#include <map>
#include <string>

#include "ballistic.id.h"
#include "ballistic.component_constructor.h"

#include "ballistic.generics.h"

namespace ballistic {

	class icomponent;

	typedef generic_singleton < 
		generic_factory	< 
			icomponent *,
			icomponent_constructor *
		>
	> component_factory;

}
#endif