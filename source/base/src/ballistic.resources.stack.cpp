#include "ballistic.resources.stack.h"

#include "ballistic.debug.h"
#include "ballistic.resources.iloader.h"
#include "ballistic.resources.istorage.h"

#include "ballistic.resources.storage_filesystem.h"

#include "ballistic.resources.package_loader.h"

namespace ballistic {
	namespace resources {
	
	stack::stack () {
		// add default storage to list
		_storage_handlers.push_back ( new resources::storage_filesystem ());
		
		_package_loader = new package_loader ();
		register_loader(_package_loader);
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
		if (loader)
			_loaders.push_back (loader);
		else
			debug_print ("[ballistic::resource::stack::register_loader] Tried to register null instance resource loader");
	}
	
	void stack::register_storage(istorage *storage) {
		if (storage)
			_storage_handlers.push_back(storage);
		else
			debug_print ("[ballistic::resource::stack::register_storage] Tried to register null instance resource storage handler");
	}
		
	istorage * stack::find_storage(const string &source) {
		for ( istorage * storage : _storage_handlers)
			if (storage->contains(source))
				return storage;
		
		debug_print ("[ballistic::resource::stack::find_storage] Storage type for source: " << source << " not found!");
		return nullptr;
	}
		
	package_loader * stack::get_package_loader() {
		return _package_loader;
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
		_resources [text_to_id (name.c_str ())] = resource;
		return *this;
	}
	
	stack & stack::add_to_level(id_t res_id, ballistic::resources::iresource *resource){
		_resources [res_id] = resource;
		if (_stacked_resources.size () > 0)
			_stacked_resources.front ().push_back(res_id);
		
		return *this;
	}
		
	stack & stack::add_to_level(const string & name, ballistic::resources::iresource *resource){
		id_t res_id = text_to_id (name.c_str ());
		
		_resources [res_id] = resource;
		if (_stacked_resources.size () > 0)
			_stacked_resources.front ().push_back(res_id);
		
		return *this;
	}
	
	iresource * stack::get_resource(id_t id) {
		resource_map_t::iterator res_it = _resources.find (id);
		if (res_it == _resources.end ()) {
			return nullptr;
		}
		
		return res_it->second;
	}
	
	iresource * stack::get_resource(const res_id_t & res_id) {
		
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
			debug_error ("[ballistic::resource::stack::get_resource] Unable to handle resource type: " << res_id.get_source ());
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
		
		debug_error ("[ballistic::resource::stack::get_resource] No appropriate storage container found for " << res_id.get_source ());
		return nullptr;
	}
		
	iresource * stack::operator [] ( const res_id_t & res_id ) {
		return get_resource (res_id);
	}


		
	}
}