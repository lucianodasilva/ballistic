//
//  ballistic.resourcestack.cpp
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#include "ballistic.resources.stack.h"
#include "ballistic.resources.storage_filesystem.h"

namespace ballistic {
	namespace resources {
	
	void stack::layer::clear () {
		for (auto res_pair : resources) {
			res_pair.second->dispose ();
			delete res_pair.second;
		}
		resources.clear ();
	}
	
	stack::layer::~layer () {
		// clean up
		clear ();
	}
	
	stack::stack () {
		// add default storage to list
		_storage_handlers.push_back ( new resources::storage_filesystem ());
	}
	
	stack::~stack() {
		for ( iloader * loader : _loaders)
			delete loader;
		
		for ( istorage * storage : _storage_handlers)
			delete storage;
		
		_stacked_resources.clear ();
		_global_resources.clear ();
	}
	
	void stack::register_loader(iloader *loader) {
		//TODO: validate nulls
		_loaders.push_back (loader);
	}
	
	void stack::register_storage(istorage *storage) {
		//TODO: validate nulls
		_storage_handlers.push_back(storage);
	}
	
	void stack::push () {
		_stacked_resources.push_front(layer ());
	}
	
	bool stack::pop () {
		if (_stacked_resources.size() > 0) {
			_stacked_resources.pop_front();
			return true;
		} else
			return false;
	}
	
	iresource * stack::get_resource(const string & name) {
		
		resource_map_t::iterator res_it;
	
		// check for loaded resources first
		for ( stack::layer & layer : _stacked_resources ) {
			res_it = layer.resources.find (name);
			
			if (res_it != layer.resources.end ())
				return res_it->second;
		}
		
		// no resource found in the stack
		// checking global resources
		res_it = _global_resources.resources.find (name);
		
		if (res_it != _global_resources.resources.end ()) {
			return res_it->second;
		}
		
		// check for a loader capable of handling the file
		iloader * loader = nullptr;
		
		for ( iloader * l_it : _loaders ) {
			if (l_it->handles(name)) {
				loader = l_it;
				break;
			}
		}
		
		// unable to handle resource type
		if (!loader)
			return nullptr;
		
		// search for container
		for (istorage * storage : _storage_handlers) {
			if (storage->contains(name)) {
				return storage->load (loader, name);
			}
		}
		
		// no container found
		return nullptr;
	}
		
	}
}