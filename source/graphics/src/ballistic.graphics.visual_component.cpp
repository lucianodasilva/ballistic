#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.system.h"

#include <glm.hpp>
#include <functional>

using namespace std;
using namespace glm;

namespace ballistic {
	namespace graphics {

		engine::attribute::id_t visual_component::mesh_attribute_id = hash < string > () ("visual_mesh");
		engine::attribute::id_t visual_component::material_attribute_id = hash < string > () ("visual_material");
		engine::attribute::id_t visual_component::transform_attribute_id = hash < string > () ("transform");

		void visual_component::setup () {
			// Reserve properties
			get_entity ()->attribute (mesh_attribute_id).set (nullptr);
			get_entity ()->attribute (material_attribute_id).set (nullptr);
		}
		
		void visual_component::notify ( ballistic::engine::message & message ) {
		
			if (message.get_id () != message_render_frame)
				return;
			
			system * v_system = message [message_render_frame_system];
			engine::entity * ent = get_entity ();

			v_system->add_render_item (
				ent->attribute (mesh_attribute_id).get().as <irenderable *>(),
				ent->attribute (transform_attribute_id).get().as <mat4>(),
				ent->attribute (material_attribute_id).get().as < material * > ()
			);
			
		}
		
	}
}