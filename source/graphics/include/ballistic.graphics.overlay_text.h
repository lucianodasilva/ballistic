#ifndef _ballistic_graphics_overlay_text_h_
#define	_ballistic_graphics_overlay_text_h_

#include <ballistic.base.h>
#include <vector>

#include "ballistic.graphics.font.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.overlay.h"

namespace ballistic {
	namespace graphics {

		class graphics_system;

		class overlay_text : public overlay {
		protected:

			property < font * > *	_overlay_font;
			property < string >	*	_overlay_text;

			imesh * _mesh;

			void generate_mesh ();

		public:

			static const id_t component_id;

			overlay_text ();
			virtual ~overlay_text();

			virtual void notify (entity * sender, ballistic::message & message) override;

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (entity * parent, ballistic::containers::property_container & parameters, ballistic::game & game_inst) override;

			virtual void terminate () override;

		};
				  
	}
}

#endif