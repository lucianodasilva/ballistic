#include "ballistic.resource_container.h"

#include "ballistic.debug.h"
#include "ballistic.iloader.h"
#include "ballistic.iresource.h"
#include "ballistic.istorage.h"

#include "ballistic.storage_filesystem.h"

#include "ballistic.package_loader.h"

namespace ballistic {
	
	resource_container::resource_container () {
		// add default storage to list
		_storage_handlers.push_back ( new storage_filesystem ());
		
		_package_loader = new package_loader ();
		register_loader(_package_loader);
	}
	
	resource_container::~resource_container() {
		for ( iloader * loader : _loaders)
			delete loader;
		
		for ( istorage * storage : _storage_handlers)
			delete storage;
		
		for (auto res_it : _resources)
			delete res_it.second;
	}
	
	void resource_container::register_loader(iloader *loader) {
		if (loader)
			_loaders.push_back (loader);
		else
			debug_print ("[ballistic::resource::resource_container::register_loader] Tried to register null instance resource loader");
	}
	
	void resource_container::register_storage(istorage *storage) {
		if (storage)
			_storage_handlers.push_back(storage);
		else
			debug_print ("[ballistic::resource::resource_container::register_storage] Tried to register null instance resource storage handler");
	}
		
	istorage * resource_container::find_storage(const string &source) {
		for ( istorage * storage : _storage_handlers)
			if (storage->contains(source))
				return storage;
		
		debug_print ("[ballistic::resource::resource_container::find_storage] Storage type for source: " << source << " not found!");
		return nullptr;
	}
		
	package_loader * resource_container::get_package_loader() {
		return _package_loader;
	}
	
	void resource_container::push () {
		_resource_containered_resources.push_front(resource_id_vector_t ());
	}
	
	bool resource_container::pop () {
		if (_resource_containered_resources.size() > 0) {
			
			for (id_t res_id : _resource_containered_resources.front()) {
				auto res_it = _resources.find (res_id);
				
				if (res_it != _resources.end ())
					delete res_it->second;
			}
			
			_resource_containered_resources.pop_front();
			return true;
		} else
			return false;
	}
	
	resource_container & resource_container::add_to_global(ballistic::iresource *resource) {
		if (resource) 
			_resources [resource->id()] = resource;
		else {
			debug_print ("empty resource instance not added");
		}

		return *this;
	}
	
	resource_container & resource_container::add_to_level(ballistic::iresource *resource){
		if (resource) {
			_resources [resource->id ()] = resource;
			if (_stacked_resources.size () > 0)
				_stacked_resources.front ().push_back (resource->id());
		} else {
			debug_print ("empty resource instance not added");
		}

		return *this;
	}
	
	iresource * resource_container::get_resource(id_t id) {
		resource_map_t::iterator res_it = _resources.find (id);
		if (res_it == _resources.end ()) {
			return nullptr;
		}
		
		return res_it->second;
	}
	
	iresource * resource_container::get_resource(const res_id_t & res_id) {
		
		iresource * res = get_resource(res_id.get_id ());
		
		if (res)
			return res;
		
		// check for a loader capable of handling the file
		iloader * loader = nullptr;
		
		for ( iloader * l_it : _loaders ) {
			if (l_it->handles(res_id.get_source())) {
				loader = l_it;
				break;
			}
		}
		
		// unable to handle resource type
		if (!loader) {
			debug_error ("[ballistic::resource::resource_container::get_resource] Unable to handle resource type: " << res_id.get_source ());
			return nullptr;
		}
		
		// search for container
		for (istorage * storage : _storage_handlers) {
			if (storage->contains(res_id.get_source ())) {
				if (storage->load (loader, res_id.get_source (), *this))     {
					return get_resource(res_id.get_id ());
				}
			}
		}
		
		debug_error ("[ballistic::resource::resource_container::get_resource] No appropriate storage container found for " << res_id.get_source ());
		return nullptr;
	}
		
	iresource * resource_container::operator [] ( const res_id_t & res_id ) {
		return get_resource (res_id);
	}


		
}