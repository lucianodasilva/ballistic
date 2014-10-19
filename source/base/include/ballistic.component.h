
#ifndef _ballistic_component_h_
#define _ballistic_component_h_

#include "ballistic.icomponent.h"
#include "ballistic.component_constructor.h"

namespace ballistic {

	class game;

	// abstract implementation
	class component : public icomponent {
	private:
		ballistic::entity * _parent;
	public:

		virtual ballistic::entity * parent () const;

		component ();

		virtual void setup (ballistic::entity * parent_v, containers::property_container & parameters);

		virtual void terminate ();

		// declare helpers
		template < class component_t >
		static inline void declare (game & game_ref, id_t id);

		template < class component_t >
		static inline void declare (game & game_ref);

	};

}

namespace ballistic {
	
	template < class component_t >
	void component::declare (game & game_ref, id_t id) {
		game_ref.resources.add_to_global (
			new component_constructor < component_t > (id)
		);
	}

	template < class component_t >
	void component::declare (game & game_ref) {
		declare < component_t > (game_ref, component_t::component_id);
	}

}

#endif
