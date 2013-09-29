#include "ballistic.graphics.visual.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"

#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"

namespace ballistic {
	namespace graphics {

		const id_t visual::component_id = ballistic::id::graphics::visual;

		void visual::setup (entity * parent, vector < ballistic::property > & parameters)
		{
			component::setup (parent, parameters);
		}

		visual::visual ()
			:
			_material (nullptr),
			_mesh (nullptr),
			_system (nullptr)
		{}

		void visual::notify ( ballistic::message & message ) {

			// if render... render :D 
			if (message.get_id () == id::message_render) {

				if (_system && _material && _material->get_effect () && _mesh)
					_system->push_item (_material, _mesh, mat4 ()); //TODO: think about transforms for rendering
				debug_run ( else
					debug_warn ("[ballistic::graphics::visual] Incomplete visual component. Will not render!");
				);

				return;
			}

			// handle property changes
			if (message.get_id () == ballistic::id::message_property_changed && 
				message.get_sender () == get_entity ()
			){
				id_t property_id = message [ballistic::id::id].as < id_t > ();

				if (property_id == id::transform)
					_transform = message [ballistic::id::value].as < mat4 > ();

				if (property_id == id::material) {
					id_t material_res_id = message [ballistic::id::value].as < id_t > ();

					_material = get_game ()->get_resource < imaterial > (material_res_id);
				}

				if (property_id == id::mesh) {
					id_t mesh_res_id = message [ballistic::id::value].as < id_t > ();
					_mesh = get_game ()->get_resource < imesh > (mesh_res_id);
				}

				return;
			}

			// if initialize load game and entity properties
			if (message.get_id () == ballistic::id::message_initialize) {

				entity * ent = get_entity ();

				_system = dynamic_cast <graphics_system *> (get_game ()->find_system (ballistic::id::graphics::system));

				_material = get_game ()->get_resource < imaterial > (ent->get_property (ballistic::id::material).as < id_t > ());
				_mesh = get_game ()->get_resource < imesh > (ent->get_property (ballistic::id::mesh).as < id_t > ());
				_transform	= ent->get_property (ballistic::id::transform).as < mat4 > ();
			}

		}

	}
}