#include <ballistic.base.h>

#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.visual.h"

#include "ballistic.graphics.resources.effect_package_type.h"
#include "ballistic.graphics.resources.material_package_type.h"
#include "ballistic.graphics.resources.mesh_package_type.h"

namespace ballistic {
	namespace graphics {

		void define_resources (ballistic::game * game, ballistic::graphics::idevice * device) {

			component::define < visual > (game);
			component::define < camera > (game);

			game->get_resource_stack ().get_package_loader ()->register_type (
				new graphics::resources::effect_package_type (device)
			);

			game->get_resource_stack ().get_package_loader ()->register_type (
				new graphics::resources::material_package_type (device)
			);

			game->get_resource_stack ().get_package_loader ()->register_type (
				new graphics::resources::mesh_package_type (device)
				);
		}

	}
}