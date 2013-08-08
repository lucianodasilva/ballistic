
namespace ballistic {

	void property::raise_property_changed_event () {
		if (_container)
			_container->property_changed_event (*this);
	}

	property::property () : _id (0), _container (nullptr) {}

	property::property (id_t id) : _id (id), _container (nullptr) {}

	property::property (iproperty_container * container, id_t id) :
		_id (id), _container (container) {}

	property::property (const property & v) : _id (v._id), _container (v._container), _value (v._value) {}

	property::operator var () const {
		return _value;
	}

	template < class T >
	property::operator T () const {
		return _value.operator T ();
	}

	template < class T >
	T property::as () const {
		return _value.as < T > ();
	}

	template < class T >
	property & property::operator = (const T & v) {
		_value.operator = < T > (v);
		raise_property_changed_event ();
		return *this;
	}

	property & property::operator = (const property & v) {
		_value = v._value;
		raise_property_changed_event ();
		return *this;
	}

	id_t property::get_id () const { return _id; }

	iproperty_container * property::get_container () const { return _container; }
	void property::set_container (iproperty_container * container) {_container = container;}

	typedef map < id_t, property > property_map_t;

}