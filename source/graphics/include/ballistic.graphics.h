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
#include "ballistic.graphics.io.effect_package_reader.h"
#include "ballistic.graphics.io.material_package_reader.h"
#include "ballistic.graphics.io.mesh_package_reader.h"
#include "ballistic.graphics.io.texture_package_reader.h"
#include "ballistic.graphics.itexture.h"
#include "ballistic.graphics.render_item.h"
#include "ballistic.graphics.render_list.h"
#include "ballistic.graphics.visual.h"

namespace ballistic {

	namespace graphics {

		void define_resources (ballistic::graphics::idevice * device);

	}
}

#endif