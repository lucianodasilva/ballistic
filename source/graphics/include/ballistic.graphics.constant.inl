
namespace ballistic {
	namespace graphics {

		template < class T >
		id_t ihardware_constant_base < T >::get_id () { return _id; }

		template < class T >
		void ihardware_constant_base < T >::set (const var & v) {
			_value = v.as < T > ();
		}

		template < class T >
		var ihardware_constant_base < T >::get () const{
			return _value;
		}

		constant::constant () : _hardware (nullptr) {}
		constant::constant (const constant & v) : _hardware (v._hardware), _value (v._value) {}
		constant::constant (ihardware_constant * v) : _hardware (v) {}

		id_t constant::get_id () const {
			if (_hardware)
				return _hardware->get_id ();
			else {
				debug_warn ("Effect constant id checked without hardware bind!");
				return 0;
			}
		}

		constant::operator var () const {
			return _value;
		}

		template < class T >
		constant::operator T () const {
			return _value.as < T > ();
		}

		void constant::bind (ihardware_constant * v) {
			_hardware = v;
		}

		template < class T >
		constant & constant::operator = (const T & v) {
			_value = v;
			return *this;
		}

		constant & constant::operator = (const constant & v) {
			_hardware = v._hardware;
			_value = v._value;

			return *this;
		}

		inline void constant::apply () {
			if (_hardware) {
				_hardware->set (_value);
				_hardware->apply ();
			} else {
				debug_warn ("Effect constant applied without hardware binding!");
			}
		}

	}
}