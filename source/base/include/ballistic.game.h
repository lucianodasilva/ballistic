#ifndef	_ballistic_game_h_
#define _ballistic_game_h_

#include "ballistic.resources.component_constructor.h"
#include "ballistic.entity.h"
#include "ballistic.ifrontend.h"
#include "ballistic.message.h"
#include "ballistic.system.h"

#include "ballistic.resources.stack.h"

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <atomic>

using namespace std;

namespace ballistic {
	
	class icomponent;

	class game : public entity {
	protected:
		
		// entity id
		atomic<unsigned int> _id_key;

		typedef map < id_t, entity * > entity_map_t;
		entity_map_t _entity_map;

		bool _running;

		void add_entity ( entity * ent );

		// game state ---
		system::ballistic_time_t
				_game_start_time,
				_frame_start;

		uint32	_frame_id;
		message _m_update;
		
		// internal systems
		resources::stack _resources;

	public:
		
		// resource handling
		
		template < class T >
		inline void define_component ( const string & id );
		
		virtual icomponent * create_component ( const res_id_t & type );
		
		virtual entity * create_entity ( const res_id_t & type );
		virtual entity * create_entity ( id_t id, const res_id_t & type );
		
		virtual resources::iresource *	get_resource (const res_id_t & res_id);
		
		virtual void push_resource_level ();
		virtual bool pop_resource_level ();
		
		resources::stack & get_resource_stack ();
		// -----------------

		virtual entity * find_entity ( id_t id );

		virtual void send_message ( ballistic::message & message );

		virtual void on_initialize ();

		virtual bool is_running ();

		virtual void do_loop (ifrontend * frontend = nullptr, function < void ( game * )> system_callback = nullptr);

		virtual bool frame ();

		virtual void terminate ();

		game ();
		virtual ~game ();

	};
	
	template < class T >
	void game::define_component ( const string & id ) {
		_resources.add_to_global ( id, new resources::component_constructor < T > () );
	}
}

#endif