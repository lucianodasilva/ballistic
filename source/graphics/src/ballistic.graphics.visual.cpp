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

			new_type->properties.require < vec3 > (id::position, vec3 ());
			new_type->properties.require < vec3 > (id::rotation, vec3 ());
			new_type->properties.require < vec3 > (id::scale, vec3 ({1, 1, 1}));
		}

		void visual::setup (entity * parent, property_container & parameters)
		{
			component::setup (parent, parameters);

			game::instance.global_notifier.attach (id::message_render, this);

			_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

			_material = parent->properties.aquire < imaterial * > (
				id::graphics::material
			);

			_mesh = parent->properties.aquire < imesh * > (
				id::graphics::mesh
			);

			_position = parent->properties.aquire < vec3 > (id::position);
			_rotation = parent->properties.aquire < vec3 > (id::rotation);
			_scale = parent->properties.aquire < vec3 > (id::scale);

			if (!*_material)
				*_material = game::instance.resources [
					parent->properties [id::graphics::material_id].as < id_t >()
				].as < imaterial > () ;

			if (!*_mesh)
				*_mesh = game::instance.resources [
					parent->properties [id::graphics::mesh_id].as < id_t > ()
				].as < imesh > ();
		}

		void visual::terminate () {
			game::instance.global_notifier.detach (id::message_render, this);
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
				//TODO: handle remaining transformations
				_system->push_item (material, mesh, mat4::make_translation (*_position));
			} else {
				debug_print ("incomplete visual component. will not render!");
			}

		}

	}
}