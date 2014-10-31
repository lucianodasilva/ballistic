#ifndef _ballistic_animation_component_h_
#define _ballistic_animation_component_h_

#include "ballistic.component.h"
#include "ballistic.animation.storyboard.h"

#include <vector>

namespace ballistic {
	namespace animation {

		class game;

		class component : public ballistic::component {
		private:

			real _start_time;

			storyboard * _storyboard;
			std::vector < idriver * > _drivers;

		public:

			static const id_t component_id;

			component ();

			storyboard * storyboard ();
			std::vector < idriver * > & drivers ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::containers::property_container & parameters);

			virtual void terminate ();

			virtual void notify (ballistic::entity * sender, ballistic::message & message);

		};

	}
}

#endif