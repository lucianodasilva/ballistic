#include "ballistic.graphics.visual.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		const id_t visual::component_id = ballistic::id::graphics::visual;

		void visual::setup (entity * parent, property_container & parameters)
		{
			component::setup (parent, parameters);

			game::instance.global_notifier.attach (id::message_render, this);

			_system = dynamic_cast <graphics_system *> (game::instance.systems [ballistic::id::graphics::system]);

			_material = parent->properties.require < imaterial * > (id::material, nullptr);
			_mesh = parent->properties.require < imesh * > (id::mesh, nullptr);
			_transform = parent->properties.require < mat4 > (id::transform, mat4 ());
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

			if (
				_system && 
				material &&
				material->effect () &&
				mesh
			)
				_system->push_item (material, mesh, *_transform); //TODO: think about transforms for rendering
			debug_run ( else
				debug_print ("incomplete visual component. Will not render!");
			);

		}

	}
}