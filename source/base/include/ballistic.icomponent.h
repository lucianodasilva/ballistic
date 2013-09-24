
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_

#include "ballistic.igame.h"
#include "ballistic.message.h"
#include "ballistic.property.h"
#include "ballistic.resources.id.h"

#include <vector>

namespace ballistic {
	
	namespace resources {
		
		template < class T >
		class component_constructor;
		
	}
	
	// --------------------
	
	class icomponent {
	public:

		virtual entity * get_entity () const = 0;
		virtual void set_entity ( entity * ent ) = 0;

		virtual ~icomponent ();
			
		virtual void setup () = 0;
		virtual void setup ( vector < property > & parameters ) = 0;
			
		virtual void notify ( ballistic::message & message ) = 0;
			
	};
	
	// abstract implementation
	class component : public icomponent {
	private:
		entity * _entity;
	public:
		
		typedef void (*notify_callback)( entity & this_entity, ballistic::message & );
		
		entity * get_entity () const;
		virtual void set_entity ( entity * ent );
		
		component ();
		
		virtual void setup ();
		virtual void setup ( vector < property > & parameters );

		template < class T >
		static inline void define (ballistic::igame * game, id_t id);

		template < class T >
		static inline void define (ballistic::igame * game);

		static icomponent * create (ballistic::igame * game, const res_id_t & id);
		static icomponent * create (ballistic::igame * game, id_t id);
		static icomponent * create (ballistic::igame * game, id_t id, vector < property > & parameters);

		template < class T >
		static inline T * create (ballistic::igame * game, const res_id_t & id);

		template < class T >
		static inline T * create (ballistic::igame * game, id_t id);

		template < class T >
		static inline T * create (ballistic::igame * game, id_t id, vector < property > & parameters);

		template < class T >
		static inline T * create (ballistic::igame * game);

	};

	// define and create functions

	template < class T >
	void component::define (ballistic::igame * game, id_t id) {
		game->get_resource_stack ().add_to_global (id, new ballistic::resources::component_constructor < T > ());
	}

	template < class T >
	void component::define (ballistic::igame * game) {
		define < T > (game, T::component_id);
	}

	template < class T >
	T * component::create (ballistic::igame * game, const res_id_t & id) {
		return create < T > (game, id.get_id ());
	}

	template < class T >
	T * component::create (ballistic::igame * game, id_t id) {
		static_assert (is_base_of < icomponent, T >::value, "[ballistic::component::create] Constructor template parameter must be derived from icontructor!");
		return dynamic_cast < T * > (create (game, id));
	}

	template < class T >
	T * component::create (ballistic::igame * game, id_t id, vector < property > & parameters) {
		static_assert (is_base_of < icomponent, T >::value, "[ballistic::component::create] Constructor template parameter must be derived from icontructor!");
		return dynamic_cast <T *> (create (game, id, parameters));
	}

	template < class T >
	T * component::create (ballistic::igame * game) {
		return create < T > (game, T::component_id);
	}

	// extra tools

	template < void (*message_handle)( entity & this_entity, ballistic::message & ) >
	class _func_component : public component {
	public:

		virtual inline void notify ( ballistic::message & message );

	};

	template < void (*message_handle)( entity & this_entity, ballistic::message & ) >
	void _func_component < message_handle >::notify ( ballistic::message & message ) {
		message_handle (get_entity (), message);
	}
	
}

#endif
