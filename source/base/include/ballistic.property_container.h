#ifndef	_ballistic_property_container_h_
#define _ballistic_property_container_h_

#include "ballistic.var.h"

#include <map>

namespace ballistic {

	class entity;

	class iproperty_container {
	public:

		virtual void add (id_t id, const var & v) = 0;
		virtual void remove (id_t id) = 0;

		virtual bool contains (id_t id) const = 0;

	};

	class property_map : public iproperty_container {
	private:
		std::map < id_t, var > _properties;
	public:


		virtual void add (id_t id, const var & v);
		virtual void remove (id_t id);

		virtual bool contains (id_t id) const;

		inline var & operator [] (id_t id) {
			return _properties [id];
		}

		std::map < id_t, var >::iterator begin ();
		std::map < id_t, var >::iterator end ();
	};

	class var_write_guard {
	private:

		var &					_ref;
		id_t &					_id;
		entity *				_container;

	public:

		inline var_write_guard (
			entity * container,
			var & ref,
			id_t & id
			) :
			_ref (ref), _id (id), _container (container) {}

		template < class T >
		inline T & operator = (T & v) {
			_container->property_changed_event (_id, _ref);  // raise event
			_ref.operator = (v);
			return v;
		}

		inline operator var const & () {
			return _ref;
		}

		template < class T >
		inline operator T () {
			return _ref.copy < T > ();
		}

		template < class T >
		inline T & as () {
			return _ref.as < T > ();
		}

	};

	class entity;

	class callback_property_map : public property_map {
	private:
		std::map < id_t, var > _properties;
		entity * _parent;
	public:

		callback_property_map (entity * parent);

		inline var_write_guard operator [] (id_t id) {
			return var_write_guard ( _parent, _properties [id], id);
		}

	};

}

#endif