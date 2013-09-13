#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		const id_t visual_component::component_id = ballistic::graphics::id::visual_component;

		void visual_component::setup (vector < ballistic::property > & parameters)
		{
		}

		visual_component::visual_component ()
			:
			_material (nullptr),
			_mesh (nullptr),
			_system (nullptr),
			_game (nullptr)
		{}

		void visual_component::notify ( ballistic::message & message ) {

			// if render... render :D 
			if (message.get_id () == graphics::id::message_render) {

				if (_system && _material && _material->get_effect () && _mesh)
					_system->push_item (_material, _mesh, _transform);
				debug_run ( else
					debug_warn ("[ballistic::graphics::visual_component] Incomplete visual component. Will not render!");
				);

				return;
			}

			// handle property changes
			if (message.get_id () == ballistic::id::message_property_changed && 
				message.get_sender () == get_entity ()
			){
				id_t property_id = message [ballistic::id::id].as <id_t> ();

				if (property_id == ballistic::id::transform)
					_transform = message [ballistic::id::value].as <mat4> ();

				if (property_id == graphics::id::material) {
					id_t material_res_id = message [ballistic::id::value].as < id_t > ();

					_material = _game->get_resource < imaterial > (material_res_id);
				}

				if (property_id == graphics::id::mesh) {
					id_t mesh_res_id = message [ballistic::id::value].as < id_t > ();
					_mesh = _game->get_resource < imesh > (mesh_res_id);
				}

				return;
			}

			// if initialize load game and entity properties
			if (message.get_id () == ballistic::id::message_initialize) {

				entity * ent = get_entity ();

				_game = ent->get_game ();

				_system = dynamic_cast <graphics_system *> (_game->find_system (ballistic::graphics::id::graphics_system));

				_material	= _game->get_resource < imaterial > (ent->get_property (ballistic::graphics::id::material).as < id_t > ());
				_mesh		= _game->get_resource < imesh > (ent->get_property (ballistic::graphics::id::mesh).as < id_t > ());
				_transform	= ent->get_property (ballistic::id::transform).as < mat4 > ();
			}

		}

	}
}