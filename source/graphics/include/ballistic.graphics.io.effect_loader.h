#ifndef _ballistic_graphics_io_effect_loader_h_
#define _ballistic_graphics_io_effect_loader_h_

#include <ballistic.base.h>
#include "ballistic.graphics.idevice.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			class effect_loader : public ballistic::io::iloader {
			private:

				idevice * _device;

			public:

				effect_loader (idevice * device);

				virtual bool handles (const string & name);

				virtual bool load (istream & source, uint32_t length, ballistic::resource_container & container, const id_t & id);

			};

		}
	}
}

#endif // !_ballistic_graphics_resources_effect_package_type_h_
