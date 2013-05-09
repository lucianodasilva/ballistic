#ifndef _ballistic_engine_attribute_h
#define _ballistic_engine_attribute_h

#include "ballistic.engine.common_messages.h"
#include "ballistic.engine.message.h"
#include "ballistic.var.h"

namespace ballistic {
	namespace engine {
		
		class entity;
		
		class attribute {
		public:
			typedef size_t id_t;
		private:
			
			var			_value;
			id_t		_id;
			entity *	_parent;
			
		public:
			
			attribute ();
			attribute ( entity * parent, id_t id );
			attribute ( const attribute & orig );
			
			id_t get_id ();
			
			var get () const;
			void set ( const var & v );
			
		};
		


	}
}

#endif
