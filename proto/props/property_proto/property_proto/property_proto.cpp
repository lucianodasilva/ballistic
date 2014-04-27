// property_proto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "property.h"
#include "property_container.h"


int _tmain(int argc, _TCHAR* argv[])
{
	property < int > p ("i", 0);

	containers::property_container < iproperty, property > plist;
	
	auto prop = plist.require ("23", 23);

	containers::entity_property_container entity_prop (new entity ());

	entity_prop.require_active ("lu", 13);

	return 0;
}

