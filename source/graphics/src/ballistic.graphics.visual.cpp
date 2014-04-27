#include "ballistic.graphics.visual.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		const id_t visual::component_id = ballistic::id::graphics::visual;

		void visual::require_properties (entity_type * new_type, component_info & info) {
			
			new_type->properties.require < id_t > (id::graphics::material_id, id::null);
			new_type->properties.require < id_t > (id::graphics::mesh_id, id::null);

			new_type->properties.require < imaterial * > (id::graphics::material, nullptr);
			new_type->properties.require < imesh * > (id::graphics::mesh, nullptr);

			new_type->properties.require < uint8_t > (id::graphics::layer, 0);

			new_type->properties.require < mat4 > (id::transform, mat4 ());
		}

		void visual::setup (entity * parent, containers::property_container & parameters)
		{
			component::setup (parent, parameters);

			game::instance.global_notifier.attach (id::message::render, this);

			_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

			_material = parent->properties.aquire < imaterial * > (
				id::graphics::material
			);

			_mesh = parent->properties.aquire < imesh * > (
				id::graphics::mesh
			);

			_transform = parent->properties.aquire < mat4 > (id::transform);

			if (!*_material)
				*_material = game::instance.resources [
					parent->properties [id::graphics::material_id].as < id_t >()
				].as < imaterial > () ;

			if (!*_mesh)
				*_mesh = game::instance.resources [
					parent->properties [id::graphics::mesh_id].as < id_t > ()
				].as < imesh > ();

			_layer = parent->properties.aquire < uint8_t > (id::graphics::layer);
		}

		void visual::terminate () {
			game::instance.global_notifier.detach (id::message::render, this);
		}

		visual::visual ()
			:
			_material (nullptr),
			_mesh (nullptr),
			_system (nullptr)
		{}

		void visual::notify ( entity * sender, ballistic::message & message ) {

			imaterial * material = *_material;
			imesh * mesh = *_mesh;



			if (!material) {
				debug_print ("missing material instance. will not render");
				return;
			}

			if (
				_system &&
				material &&
				material->effect () &&
				mesh
			){
				_system->push_item (material, mesh, *_layer, *_transform);
			} else {
				debug_print ("incomplete visual component. will not render!");
			}

		}

	}
}