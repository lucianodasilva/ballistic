
namespace ballistic
{

	//template < class T >
	//generic_singleton < T > * generic_singleton < T >::_instance = nullptr;

	template < class T >
	generic_singleton < T > & generic_singleton < T >::instance () {
		if (!_instance)
			_instance = new generic_singleton < T > ();

		return *_instance;
	}

	// generic factory
	template < class T, class ctor_T >
	void generic_factory < T, ctor_T >::define ( const string & name_id, ctor_T ctor_inst ) {
		define (string_to_id (name_id), ctor_inst);
	}

	template < class T, class ctor_T >
	void generic_factory < T, ctor_T >::define ( id_t id, ctor_T ctor_inst ) {
		_const_inst [id] = ctor_inst;
	}

	template < class T, class ctor_t >
	bool generic_factory < T, ctor_t >::contains ( const string & name_id ) const{
		return contains (string_to_id (name_id));
	}

	template < class T, class ctor_T >
	bool generic_factory < T, ctor_T >::contains ( id_t id ) const {
		return _const_inst.find (id) != _const_inst.end ();
	}

	template < class T, class ctor_T >
	T generic_factory < T, ctor_T >::create ( const string & name_id ) const {
		return create (string_to_id (name_id));
	}

	template < class T, class ctor_T >
	T generic_factory < T, ctor_T >::create ( id_t id ) const {
		auto it = _const_inst.find (id);

		if (it != _const_inst.end ()) {
			return indirection < ctor_T >::demote (it->second).create ();
		} else {
			throw "Constructor unregistered";
		}
	}

	template < class T >
	T & indirection < T >::demote ( T & inst ) {
		return inst;
	}

	template < class T >
	T & indirection < T * >::demote ( T * inst ) {
		return *inst;
	}

}