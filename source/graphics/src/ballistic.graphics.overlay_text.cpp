#include "ballistic.graphics.overlay_text.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.material.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		void overlay_text::generate_mesh () {

		}

		void overlay_text::require_properties (entity_type * new_type, component_info & info) {
			visual::require_properties (new_type, info);
			new_type->properties.require_notify < std::string > (id::graphics::graphics_text, "");
		}

		const id_t overlay_text::component_id = ballistic::id::graphics::overlay_text;

		overlay_text::overlay_text ()
			:
			overlay (),
			_overlay_text (nullptr)
		{}

		void overlay_text::setup (entity * parent, ballistic::containers::property_container & parameters) {
			overlay::setup (parent, parameters);

			// erase mesh from parent's properties and make it "dynamic"
			parent->properties.remove (id::graphics::mesh);

			_overlay_text = parent->properties.aquire < std::string > (id::graphics::overlay_text);
			parent->local_notifier.attach (id::message::property_changed, this);

			generate_mesh ();
		}

		void overlay_text::terminate () {
			overlay::terminate ();
			this->parent ()->local_notifier.detach (id::message::render, this);
		}

		void overlay_text::notify (entity * sender, ballistic::message & message) {
			if (message.id () == id::message::property_changed) {
				generate_mesh ();
				return;
			}

			material * mat = *_material;
			imesh * mesh = *_mesh;

			if (!mat) {
				debug_print ("missing material instance. will not render");
				return;
			}

			if (
				_system &&
				mat &&
				mesh
			){
				_system->push_overlay_item (mat, mesh, *_layer, *_transform);
			} else {
				debug_print ("incomplete overlay component. will not render!");
			}
		}

	}
}