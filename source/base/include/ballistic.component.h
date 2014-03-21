
#ifndef _ballistic_component_h_
#define _ballistic_component_h_

#include "ballistic.icomponent.h"
#include "ballistic.component_constructor.h"

namespace ballistic {

	// abstract implementation
	class component : public icomponent {
	private:
		ballistic::entity * _container;
	public:

		virtual ballistic::entity * container () const;

		component ();

		virtual void setup (ballistic::entity * container_v, property_container & parameters);
		
		virtual void terminate ();

		// declare helpers
		template < class component_t >
		static inline void declare (id_t id);

		template < class component_t >
		static inline void declare ();

	};

	template < class component_t >
	void component::declare (id_t id) {
		game::instance.resources.add_to_global (
			new component_constructor < component_t > (id)
			);
	}

	template < class component_t >
	void component::declare () {
		declare < component_t > (component_t::component_id);
	}

}

#endif
