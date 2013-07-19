//
//  ballistic.resourcestack.cpp
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#include "ballistic.resources.stack.h"
#include "ballistic.resources.iloader.h"
#include "ballistic.resources.istorage.h"
#include "ballistic.resources.storage_filesystem.h"

namespace ballistic {
	namespace resources {
	
	stack::stack () {
		// add default storage to list
		_storage_handlers.push_back ( new resources::storage_filesystem ());
	}
	
	stack::~stack() {
		for ( iloader * loader : _loaders)
			delete loader;
		
		for ( istorage * storage : _storage_handlers)
			delete storage;
		
		for (auto res_it : _resources)
			delete res_it.second;
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
		_stacked_resources.push_front(resource_id_vector_t ());
	}
	
	bool stack::pop () {
		if (_stacked_resources.size() > 0) {
			
			for (id_t res_id : _stacked_resources.front()) {
				auto res_it = _resources.find (res_id);
				
				if (res_it != _resources.end ())
					delete res_it->second;
			}
			
			_stacked_resources.pop_front();
			return true;
		} else
			return false;
	}
	
	stack & stack::add_to_global(id_t res_id, ballistic::resources::iresource *resource) {
		_resources [res_id] = resource;
		return *this;
	}
	
	stack & stack::add_to_global(const string & name, ballistic::resources::iresource *resource) {
		_resources [string_to_id (name)] = resource;
		return *this;
	}
	
	stack & stack::add_to_level(id_t res_id, ballistic::resources::iresource *resource){
		_resources [res_id] = resource;
		if (_stacked_resources.size () > 0)
			_stacked_resources.front ().push_back(res_id);
		
		return *this;
	}
		
	stack & stack::add_to_level(const string & name, ballistic::resources::iresource *resource){
		id_t res_id = string_to_id (name);
		
		_resources [res_id] = resource;
		if (_stacked_resources.size () > 0)
			_stacked_resources.front ().push_back(res_id);
		
		return *this;
	}
	
	iresource * stack::get_resource(const res_id_t & res_id) {
		
		resource_map_t::iterator res_it;
	
		// check for loaded resources first
		resource_map_t::iterator loaded_id = _resources.find (res_id);
		
		if (loaded_id != _resources.end ())
			return loaded_id->second;
		
		// check for a loader capable of handling the file
		iloader * loader = nullptr;
		
		for ( iloader * l_it : _loaders ) {
			if (l_it->handles(res_id.get_source())) {
				loader = l_it;
				break;
			}
		}
		
		// unable to handle resource type
		if (!loader)
			return nullptr;
		
		// search for container
		for (istorage * storage : _storage_handlers) {
			if (storage->contains(res_id.get_source ())) {
				return storage->load (loader, res_id.get_source(), *this);
			}
		}
		
		// no container found
		return nullptr;
	}
		
	iresource * stack::operator [] ( const res_id_t & res_id ) {
		return get_resource (res_id);
	}
		
	}
}