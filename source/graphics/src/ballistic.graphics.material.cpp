#include "ballistic.graphics.material.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		material::material (const id_t & id) : 
			iresource (id),
			texture (nullptr),
			diffuse({ real(1), real(1), real(1), real(1) })
		{}

		material::~material() {}
	}
}