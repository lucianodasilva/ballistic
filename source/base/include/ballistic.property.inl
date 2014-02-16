
namespace ballistic {

	void property::raise_property_changed_event () {
		if (_container)
			_container->property_changed_event (*this);
	}

	void property::swap (property & v) {
		id_t t_id						  = _id;
		iproperty_container * t_container = _container;

		_id = v._id;
		_container = v._container;
		v._id = t_id;
		v._container = t_container;

		_value.swap (v._value);
	}

	property::property () : _id (0), _container (nullptr) {}

	property::property (id_t id) : _id (id), _container (nullptr) {}

	property::property (iproperty_container * container, id_t id) :
		_id (id), _container (container) {}

	property::property (const property & v) : _value (v._value), _id (v._id), _container (v._container) {}

	property::property (property && v) {
		this->swap ( v);
	}

	template < class T >
	T property::as () const {
		return _value.as < T > ();
	}

	template < class T >
	property & property::operator = (const T & v) {
		//_value.operator = < T > (v);
		_value = v;
		raise_property_changed_event ();
		return *this;
	}

	property & property::operator = (property v) {
		swap (v);
		raise_property_changed_event ();
		return *this;
	}

	id_t property::get_id () const { return _id; }

	var property::get_value () const { return _value; }
	void property::set_value (var v) { _value.swap (v); }

	iproperty_container * property::get_container () const { return _container; }
	void property::set_container (iproperty_container * container) {_container = container;}

	typedef map < id_t, property > property_map_t;

}