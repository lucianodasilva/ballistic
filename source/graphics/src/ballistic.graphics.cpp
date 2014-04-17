#include <ballistic.base.h>

#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.idevice.h"
#include "ballistic.graphics.graphics_system.h"
#include "ballistic.graphics.visual.h"

#include "ballistic.graphics.io.effect_package_reader.h"
#include "ballistic.graphics.io.material_package_reader.h"
#include "ballistic.graphics.io.mesh_package_reader.h"
#include "ballistic.graphics.io.texture_package_reader.h"

#include "ballistic.graphics.ieffect.h"
#include "ballistic.graphics.imaterial.h"
#include "ballistic.graphics.imesh.h"
#include "ballistic.graphics.iraster_font.h"
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

			g.resources.package_loader ()->register_reader (
				new graphics::io::texture_package_reader (device)
			);

			// default resources

			// quad one
			// create geometry
			imesh * mesh_quad_one = device->create_mesh (id::graphics::mesh_quad_one);
			ballistic::game::instance.resources.add_to_global (mesh_quad_one);

			real vertex_data [] = {
				real (-.5), real (-.5), real (0), real (0), real (0),
				real (.5), real (-.5), real (0), real (1), real (0),
				real (.5), real (.5), real (0), real (1), real (1),
				real (-.5), real (.5), real (0), real (0), real (1)
			};

			uint16_t index_data [] = {
				0, 1, 2, 0, 2, 3
			};

			mesh_quad_one->set_data (
				(uint8_t *)+vertex_data,
				20 * sizeof (real),
				+index_data,
				6 * sizeof (uint16_t),
				(mesh_attribute)(mesh_attribute_position | mesh_attribute_uv),
				false
			);
		}

		// default constructors for resource objects
		ieffect::ieffect (const id_t & id) : iresource (id) {}

		imaterial::imaterial (const id_t & id) : iresource (id) {}

		imesh::imesh (const id_t & id) : iresource (id) {}

		itexture::itexture (const id_t & id) : iresource (id) {}

		iraster_font::iraster_font (const id_t & id) : imaterial (id) {}

	}
}