#ifndef	_ballistic_graphics_material_h_
#define _ballistic_graphics_material_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class material : public resources::iresource, public property_container {
		private:

			static void material_property_type_reader (
				const string & type,
				const string & value,
				ballistic::resources::stack & stack,
				var & out_value
			);

		private:

		};

	}
}

#endif