
#ifndef _ballistic_io_animation_storyboard_reader_h_
#define _ballistic_io_animation_storyboard_reader_h_

#include "ballistic.config.h"
#include "ballistic.debug.h"

#include "ballistic.io.package_loader.h"
#include "ballistic.animation.storyboard.h"

namespace ballistic {

	class entity_type;

	namespace io {

		class animation_storyboard_reader : public ipackage_group_reader {
		private:

			void load_action (
				const tinyxml2::XMLElement * element,
				ballistic::resource_container & container,
				animation::storyboard * new_story
				);


		public:

			virtual const char * type () const;

			virtual void load_element (const tinyxml2::XMLElement * element, ballistic::resource_container & container);

		};

	}
}

#endif
