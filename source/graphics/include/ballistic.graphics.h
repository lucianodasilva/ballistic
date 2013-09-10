#ifndef _ballistic_graphics_h_
#define _ballistic_graphics_h_

#define BALLISTIC_GRAPHICS_EXPORT

#include "ballistic.graphics.camera.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.itexture.h"
#include "ballistic.graphics.render_item.h"
#include "ballistic.graphics.render_list.h"
#include "ballistic.graphics.system_component.h"
#include "ballistic.graphics.visual_component.h"

namespace ballistic {

	class game;

	namespace graphics {

		extern void define_resources (ballistic::game * game, ballistic::graphics::idevice * device);

	}
}

#endif