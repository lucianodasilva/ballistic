
namespace ballistic {

	void property::raise_property_changed_event () {
		if (_container)
			_container->property_changed_event (*this);
	}

	void property::swap (property & v1, property & v2) {
		id_t t_id						  = v1._id;
		iproperty_container * t_container = v1._container;

		v1._id = v2._id;
		v1._container = v2._container;
		v2._id = t_id;
		v2._container = t_container;

		var::swap (v1._value, v2._value);
	}

	property::property () : _id (0), _container (nullptr) {}

	property::property (id_t id) : _id (id), _container (nullptr) {}

	property::property (iproperty_container * container, id_t id) :
		_id (id), _container (container) {}

	property::property (const property & v) : _value (v._value), _id (v._id), _container (v._container) {}

	property::property (property && v) {
		swap (*this, v);
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
		swap (*this, v);
		raise_property_changed_event ();
		return *this;
	}

	id_t property::get_id () const { return _id; }

	var property::get_value () const { return _value; }
	void property::set_value (var v) { var::swap (_value, v); }

	iproperty_container * property::get_container () const { return _container; }
	void property::set_container (iproperty_container * container) {_container = container;}

	typedef map < id_t, property > property_map_t;

}