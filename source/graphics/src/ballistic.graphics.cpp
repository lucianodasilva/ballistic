#include <ballistic.base.h>

#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.visual.h"

#include "ballistic.graphics.io.effect_package_reader.h"
#include "ballistic.graphics.io.material_package_reader.h"
#include "ballistic.graphics.io.mesh_package_reader.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.itexture.h"

namespace ballistic {
	namespace graphics {

		void define_resources (ballistic::graphics::idevice * device) {

			component::declare < visual > ();
			component::declare < camera > ();

			game & g = game::instance;

			g.resources.package_loader ()->register_reader (
				new graphics::io::effect_package_reader (device)
			);

			g.resources.package_loader ()->register_reader (
				new graphics::io::material_package_reader (device)
			);

			g.resources.package_loader ()->register_reader (
				new graphics::io::mesh_package_reader (device)
			);
		}

		// default constructors for resource objects
		ieffect::ieffect (const id_t & id) : iresource (id) {}

		imaterial::imaterial (const id_t & id) : iresource (id) {}

		imesh::imesh (const id_t & id) : iresource (id) {}

		itexture::itexture (const id_t & id) : iresource (id) {}

	}
}