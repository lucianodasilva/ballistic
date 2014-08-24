#include "ballistic.graphics.io.effect_loader.h"
#include "ballistic.graphics.ieffect.h"

namespace ballistic {
	namespace graphics {
		namespace io {

			effect_loader::effect_loader (idevice * device) : _device (device) {}

			bool effect_loader::handles (const string & name) {
				if (name.size () < 3)
					return false;

				return name.compare (name.size () - 3, 3, ".fx") == 0;
			}

			bool effect_loader::load (istream & source, uint32_t length, ballistic::resource_container & container, const id_t & id) {

				char * buffer = new char [length];
				source.read (buffer, length);

				try {

					ieffect * effect = _device->create_effect (id);
					effect->load (buffer, length);
					delete [] buffer;

					container.add_to_level (effect);

				} catch (...) {
					debug_print ("exception while loading effect " << id);
					return false;
				}

				return true;
			}

		}
	}
}