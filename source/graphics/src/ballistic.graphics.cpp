#include <ballistic.base.h>

#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.system_component.h"
#include "ballistic.graphics.visual_component.h"

#include "ballistic.graphics.resources.material_package_type.h"
#include "ballistic.graphics.resources.mesh_package_type.h"

namespace ballistic {
	namespace graphics {

		void define_resources (ballistic::game * game, ballistic::graphics::idevice * device) {

			game->define_component < system_component >
				(ballistic::graphics::id::system_component);
			game->define_component < visual_component >
				(ballistic::graphics::id::visual_component);

			game->get_resource_stack ().get_package_loader ()->register_type (
				new graphics::resources::material_package_type (device)
			);

			game->get_resource_stack ().get_package_loader ()->register_type (
				new graphics::resources::mesh_package_type (device)
			);
		}

	}
}