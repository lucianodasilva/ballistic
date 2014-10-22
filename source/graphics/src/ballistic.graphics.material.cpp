#include "ballistic.graphics.material.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		material::material (const id_t & id) : 
			iresource (id),
			diffuse({ real(1), real(1), real(1), real(1) }),
			texture (nullptr)
		{}

		material::~material() {}
	}
}