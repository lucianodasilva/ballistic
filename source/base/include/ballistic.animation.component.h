#ifndef _ballistic_animation_component_h_
#define _ballistic_animation_component_h_

#include "ballistic.icomponent.h"
#include "ballistic.animation.storyboard.h"

namespace ballistic {
	namespace animation {

		class component : public ballistic::component {
		private:

			storyboard * _storyboard;

		public:

			storyboard * storyboard ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::entity * parent, ballistic::property_container & parameters);

			virtual void terminate ();

			virtual void notify (ballistic::entity * sender, ballistic::message & message);

		};

	}
}

#endif