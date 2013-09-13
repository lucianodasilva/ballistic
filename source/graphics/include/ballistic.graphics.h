#ifndef _ballistic_graphics_h_
#define _ballistic_graphics_h_

#define BALLISTIC_GRAPHICS_EXPORT

#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.itexture.h"
#include "ballistic.graphics.render_item.h"
#include "ballistic.graphics.render_list.h"
#include "ballistic.graphics.visual_component.h"
#include "ballistic.graphics.resources.effect_package_type.h"
#include "ballistic.graphics.resources.material_package_type.h"
#include "ballistic.graphics.resources.mesh_package_type.h"

namespace ballistic {

	class game;

	namespace graphics {

		extern void define_resources (ballistic::game * game, ballistic::graphics::idevice * device);

	}
}

#endif