
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

		virtual entity *	get_entity () const = 0;
		virtual igame *		get_game () const = 0;

		virtual ~icomponent ();
			
		virtual void setup ( entity * parent ) = 0;
		virtual void setup ( entity * parent, vector < property > & parameters ) = 0;
			
		virtual void notify ( ballistic::message & message ) = 0;
			
	};
	
	// abstract implementation
	class component : public icomponent {
	private:

		entity * _entity;
		igame * _game;
	public:
		
		typedef void (*notify_callback)( entity & this_entity, ballistic::message & );
		
		virtual entity * get_entity () const;
		virtual igame * get_game () const;
		
		component ();
		
		virtual void setup ( entity * parent );
		virtual void setup ( entity * parent, vector < property > & parameters );

		template < class T >
		static inline void define (ballistic::igame * game, id_t id);

		template < class T >
		static inline void define (ballistic::igame * game);

		static icomponent * create (entity * parent, const res_id_t & id);
		static icomponent * create (entity * parent, id_t id);
		static icomponent * create (entity * parent, id_t id, vector < property > & parameters);

		template < class T >
		static inline T * create (entity * parent, const res_id_t & id);

		template < class T >
		static inline T * create (entity * parent, id_t id);

		template < class T >
		static inline T * create (entity * parent, id_t id, vector < property > & parameters);

		template < class T >
		static inline T * create (entity * parent);

	};

	// define and create functions

	template < class T >
	void component::define (igame * game, id_t id) {
		game->get_resource_stack ().add_to_global (id, new ballistic::resources::component_constructor < T > ());
	}

	template < class T >
	void component::define (igame * game) {
		define < T > (game, T::component_id);
	}

	template < class T >
	T * component::create (entity * parent, const res_id_t & id) {
		return create < T > (game, id.get_id ());
	}

	template < class T >
	T * component::create (entity * parent, id_t id) {
		static_assert (is_base_of < icomponent, T >::value, "[ballistic::component::create] Constructor template parameter must be derived from icontructor!");
		return dynamic_cast < T * > (create (game, id));
	}

	template < class T >
	T * component::create (entity * parent, id_t id, vector < property > & parameters) {
		static_assert (is_base_of < icomponent, T >::value, "[ballistic::component::create] Constructor template parameter must be derived from icontructor!");
		return dynamic_cast <T *> (create (game, id, parameters));
	}

	template < class T >
	T * component::create (entity * parent) {
		return create < T > (game, T::component_id);
	}

	// extra tools

	template < void (*message_handle)( entity * parent, ballistic::message & ) >
	class _func_component : public component {
	public:

		virtual inline void notify ( ballistic::message & message );

	};

	template < void (*message_handle)( entity * parent, ballistic::message & ) >
	void _func_component < message_handle >::notify ( ballistic::message & message ) {
		message_handle (get_entity (), message);
	}
	
}

#endif
