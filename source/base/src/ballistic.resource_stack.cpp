//
//  ballistic.resourcestack.cpp
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#include "ballistic.resource_stack.h"

namespace ballistic {
	
	void resource_stack::resource_stack_layer::clear () {
		resource_map_t::iterator
		it = resources.begin (),
		end = resources.end ();
		
		while (it != end) {
			it->second->dispose ();
			delete it->second;
			++it;
		}
		
		resources.clear ();
	}
	
	resource_stack::resource_stack_layer::~resource_stack_layer () {
		// clean up
		clear ();
	}
	
	resource_stack::~resource_stack() {
		for ( resources::iloader * loader : _loaders)
			delete loader;
		
		for ( resources::istorage * storage : _storage_handlers)
			delete storage;
		
		_stacked_resources.clear ();
		_global_resources.clear ();
	}
	
	void resource_stack::register_loader(resources::iloader *loader) {
		//TODO: validate nulls
		_loaders.push_back (loader);
	}
	
	void resource_stack::register_storage(resources::istorage *storage) {
		//TODO: validate nulls
		_storage_handlers.push_back(storage);
	}
	
	void resource_stack::push () {
		_stacked_resources.push_front(resource_stack_layer ());
	}
	
	bool resource_stack::pop () {
		if (_stacked_resources.size() > 0) {
			_stacked_resources.pop_front();
			return true;
		} else
			return false;
	}
	
	resources::iresource * resource_stack::get_resource(const string & name) {
		
		resource_map_t::iterator res_it;
	
		// check for loaded resources first
		for ( resource_stack_layer & layer : _stacked_resources ) {
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
		resources::iloader * loader = nullptr;
		
		for ( resources::iloader * l_it : _loaders ) {
			if (l_it->handles(name)) {
				loader = l_it;
				break;
			}
		}
		
		// unable to handle resource type
		if (!loader)
			return nullptr;
		
		// search for container
		for (resources::istorage * storage : _storage_handlers) {
			if (storage->contains(name)) {
				return storage->load (loader, name);
			}
		}
		
		// no container found
		return nullptr;
	}
	
}