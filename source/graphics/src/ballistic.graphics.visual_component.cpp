#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.system_component.h"

namespace ballistic {
	namespace graphics {

		void visual_component::setup (vector < ballistic::property > & parameters)
		{

			for (ballistic::property & prop : parameters) {

				ballistic::id_t prop_id = prop.get_id ();

				if (prop_id == ballistic::graphics::id::material)
					_material = prop.as <imaterial *> ();
				else if (prop_id == ballistic::graphics::id::mesh)
					_mesh = prop.as < imesh * >();
			}

		}

		visual_component::visual_component ()
			:
			_material (nullptr),
			_mesh (nullptr),
			_system (nullptr) 
		{}

		void visual_component::notify ( ballistic::message & message ) {

			// if render... render :D 
			if (message.get_id () == graphics::id::message_render) {
				_system->push_item (_material, _mesh, _transform);
				return;
			}

			// handle property changes
			if (message.get_id () == ballistic::id::message_property_changed && 
				message.get_sender () == get_entity ()
			){
				id_t property_id = message [ballistic::id::id];

				if (property_id == ballistic::id::transform)
					_transform = message [ballistic::id::value];

				if (property_id == graphics::id::material)
					_material = message [ballistic::id::value];

				if (property_id == graphics::id::mesh)
					_mesh = message [ballistic::id::value];

				return;
			}

			// if initialize load game and entity properties
			if (message.get_id () == ballistic::id::message_initialize) {

				_system = message [graphics::id::system_component];

				entity * ent = get_entity ();

				_material	= ent->get_property (ballistic::graphics::id::material);
				_mesh		= ent->get_property (ballistic::graphics::id::mesh);
				_transform	= ent->get_property (ballistic::id::transform);
			}

		}

	}
}