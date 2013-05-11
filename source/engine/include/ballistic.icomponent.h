
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_

#include "ballistic.message.h"

namespace ballistic {

	class entity;
	
	class icomponent {
	private:

		entity * _entity;

	public:

		entity & get_entity () const;
		virtual void set_entity ( entity * ent );

		icomponent ();
		virtual ~icomponent ();
			
		virtual void setup ();
			
		virtual void notify ( ballistic::message & message ) = 0;
			
	};

	template < void (*message_handle)( entity & this_entity, ballistic::message & ) >
	class func_component : public icomponent {
	public:

		virtual inline void notify ( ballistic::message & message );

	};

	template < void (*message_handle)( entity & this_entity, ballistic::message & ) >
	void func_component < message_handle >::notify ( ballistic::message & message ) {
		message_handle (get_entity (), message);
	}

}

#endif
