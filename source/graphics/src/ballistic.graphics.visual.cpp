#include "ballistic.graphics.visual.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.material.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.rig.h"

namespace ballistic {
	namespace graphics {

		const id_t visual::component_id = ballistic::id::graphics::visual;

		void visual::require_properties (entity_type * new_type, component_info & info) {
			
			new_type->properties
				.require < id_t > (id::graphics::material_id, id::null)
				.require < id_t > (id::graphics::mesh_id, id::null)
				.require < id_t > (id::graphics::rig_id, id::null)
				.require < material * > (id::graphics::material, nullptr)
				.require < imesh * > (id::graphics::mesh, nullptr)
				.require < rig_frame_tween * > (id::graphics::rig_tween, &rig_frame_tween::null_frame_tween)
				.require < uint8_t > (id::graphics::layer, 0)
				.require < mat4 > (id::transform, mat4 ());
		}

		void visual::setup (entity * parent, ballistic::containers::property_container & parameters, ballistic::game & game_inst)
		{
			component::setup (parent, parameters, game_inst);

			parent->game ().global_notifier.attach (id::message::render, this);

			_system = dynamic_cast <graphics_system *> (parent->game ().systems [ballistic::id::graphics::system]);

			_material = parent->properties.aquire < material * > (
				id::graphics::material
			);

			_mesh = parent->properties.aquire < imesh * > (
				id::graphics::mesh
			);

			_transform = parent->properties.aquire < mat4 > (id::transform);

			if (!*_material)
				*_material = parent->game ().resources [
					parent->properties [id::graphics::material_id].as < id_t >()
				].as < material > () ;

			if (!*_mesh)
				*_mesh = parent->game ().resources [
					parent->properties [id::graphics::mesh_id].as < id_t > ()
				].as < imesh > ();

			_rig_tween = parent->properties.aquire < rig_frame_tween * > (id::graphics::rig_tween);

			_layer = parent->properties.aquire < uint8_t > (id::graphics::layer);
		}

		void visual::terminate () {
			parent ()->game ().global_notifier.detach (id::message::render, this);
		}

		visual::visual ()
			:
			_material (nullptr),
			_rig_tween (nullptr),
			_mesh (nullptr),
			_system (nullptr)
		{}

		void visual::notify ( entity * sender, ballistic::message & message ) {

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
				_system->push_item (mat, mesh, *_rig_tween, *_layer, *_transform);
			} else {
				debug_print ("incomplete visual component. will not render!");
			}

		}

	}
}