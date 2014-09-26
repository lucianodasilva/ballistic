#include "ballistic.resource_container.h"

#include "ballistic.debug.h"
#include "ballistic.io.iloader.h"
#include "ballistic.iresource.h"
#include "ballistic.io.istorage.h"

#include "ballistic.io.storage_filesystem.h"

#include "ballistic.io.package_loader.h"

namespace ballistic {
	
	resource_container::resource_container () {
		// add default storage to list
		_storage_handlers.push_back ( new io::storage_filesystem ());
		
		_package_loader = new io::package_loader ();
		register_loader(_package_loader);
	}
	
	resource_container::~resource_container() {
		for ( io::iloader * loader : _loaders)
			delete loader;
		
		for ( io::istorage * storage : _storage_handlers)
			delete storage;
		
		for (auto res_it : _resources)
			delete res_it.second;
	}
	
	void resource_container::register_loader(io::iloader *loader) {
		if (loader)
			_loaders.push_back (loader);
		else
			debug_print ("tried to register null instance resource loader");
	}
	
	void resource_container::register_storage(io::istorage *storage) {
		if (storage)
			_storage_handlers.push_back(storage);
		else
			debug_print ("tried to register null instance resource storage handler");
	}
		
	io::istorage * resource_container::find_storage(const string &source) {
		for ( io::istorage * storage : _storage_handlers)
			if (storage->contains(source))
				return storage;
		
		debug_print ("storage type for source: " << source << " not found!");
		return nullptr;
	}
		
	io::package_loader * resource_container::package_loader() {
		return _package_loader;
	}
	
	void resource_container::push_level () {
		_stacked_resources.push_back(resource_id_vector_t ());
	}
	
	bool resource_container::pop_level () {
		if (_stacked_resources.size () > 0) {
			
			for (id_t res_id : _stacked_resources.front ()) {
				auto res_it = _resources.find (res_id);
				
				if (res_it != _resources.end ())
					delete res_it->second;
			}
			
			_stacked_resources.pop_back ();
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
		
		iresource * res = get_resource(res_id.id ());
		
		if (res)
			return res;

		if (load (res_id.source (), res_id.id ()))
			return get_resource (res_id.id ());
		else
			return nullptr;
	}

	bool resource_container::load (const string & source) {
		id_t id = text_to_id (source.c_str ());
		return load (source, id);
	}

	bool resource_container::load (const string & source, const id_t & id) {
		// check for a loader capable of handling the file
		io::iloader * loader = nullptr;

		for (io::iloader * l_it : _loaders) {
			if (l_it->handles (source)) {
				loader = l_it;
				break;
			}
		}

		// unable to handle resource type
		if (!loader) {
			debug_error ("unable to handle resource type: " << source);
			return false;
		}

		// search for container
		for (io::istorage * storage : _storage_handlers) {
			if (storage->contains (source)) {
				return storage->load (loader, source, *this, id);
			}
		}

		debug_error ("no appropriate storage container found for " << source);

		return false;
	}
	
}