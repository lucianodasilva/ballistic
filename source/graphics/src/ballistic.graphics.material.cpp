#include "ballistic.graphics.material.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		material::material (const id_t & id) :
			iresource (id),
			diffuse ({real (1), real (1), real (1)}),
			color_mask ({real (1), real (1), real (1)}),
			ambient_sky ({real (.76), real (.83), real(.89)}),
			ambient_ground ({real (.07), real (.11), real (.13)}),
			specular_hardness (real (100)),
			specular_intensity (real (0.8)),
			ambient_intensity (real (0.05)),
			opacity (1),
			blended (false),
			texture (nullptr)
		{}

		material::~material() {}
	}
}