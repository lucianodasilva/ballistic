#ifndef _property_h_
#define _property_h_

#include <string>
#include <iostream>

typedef std::string id_t;

class iproperty {
protected:
	id_t _id;
public:

	inline id_t id () const { return _id; }

	inline iproperty (const id_t & id) : _id (id) {}
	inline virtual ~iproperty () {}

	virtual iproperty * clone () const = 0;

};

template < class value_t >
class property : public iproperty {
protected:
	value_t _value;
public:

	inline property (const id_t & id_v, const value_t & v) : iproperty (id_v), _value (v) {}

	inline virtual void operator = (const value_t & v) { _value = v; }
	inline operator value_t () { return _value; }

	inline virtual iproperty * clone () const { return new property < value_t > (_id, _value); }

};

// ---------------------

struct entity {

	void notify () { std::cout << "property changed" << std::endl; }

};

namespace containers {
	class entity_property_container;
}


template < class value_t >
class entity_property : public property < value_t > {
protected:

	entity * _parent;

public:

	friend class containers::entity_property_container;

	inline entity_property (const id_t & id_v, const value_t & v) : property (id_v, v) {}

	inline virtual void operator = (const value_t & v) {
		_value = v;
		if (_parent)
			_parent->notify ();
	}

	inline virtual iproperty * clone () const { 
		auto p = new entity_property < value_t > (_id, _value);
		p->_parent = _parent;
		return p;
	}
};

namespace descriptors {

	class idescriptor : public iproperty {
	public:

		inline idescriptor (const id_t & id) : iproperty (id) {}

		virtual iproperty * create_property (entity * parent) = 0;

	};

	template < class value_t >
	class property : public idescriptor {
	protected:
		value_t _value;
	public:

		inline property (const id_t & id_v, const value_t & v) : idescriptor (id_v), _value (v) {}

		inline virtual iproperty * clone () const { return new property < value_t > (_id, _value); }

		inline virtual iproperty * create_property (entity * parent) {

		}

	}

}

#endif