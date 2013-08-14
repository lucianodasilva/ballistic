#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.system_component.h"

namespace ballistic {
	namespace graphics {

		visual_component::visual_component ()
			:
			_material (nullptr),
			_mesh (nullptr),
			_system (nullptr) 
		{}

		void visual_component::notify ( ballistic::message & message ) {

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

			if (message.get_id () != graphics::id::message_render)
				return;

			// 1st probable run
			if (!_system) {
				_system = message [graphics::id::system_component];

				_material = get_entity ()->get_property (graphics::id::material);
				_mesh = get_entity ()->get_property (graphics::id::mesh);
				_transform = get_entity ()->get_property (ballistic::id::transform);
			}

			_system->push_item (_material, _mesh, _transform);

		}

	}
}