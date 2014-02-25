
#ifndef _ballistic_icomponent_h_
#define _ballistic_icomponent_h_



#include <vector>

namespace ballistic {

	class entity;

	class icomponent {
	public:

		virtual ballistic::entity *	container () const = 0;

		virtual ~icomponent ();

		virtual void setup (ballistic::entity * container_v) = 0;
		virtual void setup (ballistic::entity * container_v, property_container & parameters) = 0;

	};


	// abstract implementation
	class component : public icomponent {
	private:
		ballistic::entity * _container;
	public:

		virtual ballistic::entity * container () const;

		component ();

		virtual void setup (ballistic::entity * containerv);
		virtual void setup (ballistic::entity * containerv, property_container & parameters);

	};
	
}

#endif
